using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using X39.Systems.XCG.Generators.Base.Contracts;
using X39.Systems.XCG.Generators.Base.Enums;
using X39.Systems.XCG.Generators.Base.Expressions;
using X39.Systems.XCG.Generators.Base.Parts;
using X39.Systems.XCG.Generators.Base.Statements;
using X39.Util.Collections;
using X39.Util.Console;

namespace X39.Systems.XCG.Generators.CSharp;

public class CSharpGenerator : Base.BaseGenerator<CSharpOptions>
{
    protected override async Task WriteFiles(
        IEnumerable<Group> functionGroups,
        string output,
        CancellationToken cancellationToken)
    {
        Directory.CreateDirectory(output);
        foreach (var functionGroup in functionGroups)
        {
            var filePath = Path.Combine(output, functionGroup.Identifier + ".cs");

            new ConsoleString($"Writing {filePath}")
            {
                Foreground = ConsoleColor.Black,
                Background = ConsoleColor.Green,
            }.WriteLine();
            await using var fileStream = new FileStream(filePath, FileMode.Create, FileAccess.Write, FileShare.Read);
            await using var writer = new StreamWriter(fileStream);
            await WriteClassAsync(writer, functionGroup, cancellationToken);
        }
    }

    private async Task WriteClassAsync(TextWriter writer, Group functionGroup, CancellationToken cancellationToken)
    {
        await writer.WriteLineAsync($"namespace {Options.Namespace};", cancellationToken);
        await writer.WriteLineAsync($"public class {functionGroup.Identifier}", cancellationToken);
        await writer.WriteLineAsync("{", cancellationToken);
        foreach (var state in functionGroup.States)
        {
            await writer.WriteLineAsync(
                1,
                $"private {TypeFor(state.Type)} {StateIdent(state.Identifier)};",
                cancellationToken);
        }

        foreach (var function in functionGroup.Functions)
        {
            await WriteFunctionAsync(writer, function, cancellationToken);
        }

        await writer.WriteLineAsync("}", cancellationToken);
    }

    private async Task WriteFunctionAsync(TextWriter writer, Function function, CancellationToken cancellationToken)
    {
        var parameters = string.Join(", ", function.Parameters.Select(p => $"{TypeFor(p.Type)} {p.Identifier}"));
        var identifier = FuncIdent(function.Identifier);
        var returnType = TypeFor(function.ReturnType);
        await writer.WriteLineAsync(1, $"public {returnType} {identifier}({parameters})", cancellationToken);
        await writer.WriteLineAsync(1, "{", cancellationToken);
        foreach (var statement in function.Statements)
        {
            await WriteStatementAsync(writer, 2, statement, cancellationToken);
        }

        await writer.WriteLineAsync(1, "}", cancellationToken);
    }

    private async Task WriteStatementsAsync(
        TextWriter writer,
        int indent,
        ICodeStatementsHost statementHost,
        CancellationToken cancellationToken)
    {
        foreach (var codeStatement in statementHost)
        {
            cancellationToken.ThrowIfCancellationRequested();
            await WriteStatementAsync(writer, indent, codeStatement, cancellationToken);
        }
    }

    private async Task WriteStatementAsync(
        TextWriter writer,
        int indent,
        ICodeStatement statement,
        CancellationToken cancellationToken)
    {
        string value;
        string variable;
        switch (statement)
        {
            case CaseCodeStatement caseCodeStatement:
                if (caseCodeStatement.Values.Count is 0)
                {
                    await writer.WriteLineAsync(indent, $"default:", cancellationToken);
                }
                else
                {
                    foreach (var valueExpression in caseCodeStatement.Values)
                    {
                        value = await GetExpressionStringAsync(valueExpression, cancellationToken);
                        await writer.WriteLineAsync(indent, $"case {value}:", cancellationToken);
                    }
                }

                await writer.WriteLineAsync(indent, "{", cancellationToken);
                await WriteStatementsAsync(writer, indent + 1, caseCodeStatement, cancellationToken);
                await writer.WriteLineAsync(indent, "}", cancellationToken);
                break;
            case ElseCodeStatement elseCodeStatement:
                await writer.WriteLineAsync(indent, "else", cancellationToken);
                await writer.WriteLineAsync(indent, "{", cancellationToken);
                await WriteStatementsAsync(writer, indent + 1, elseCodeStatement, cancellationToken);
                await writer.WriteLineAsync(indent, "}", cancellationToken);
                break;
            case ElseIfCodeStatement elseIfCodeStatement:
                value = await GetExpressionStringAsync(elseIfCodeStatement.Condition, cancellationToken);
                await writer.WriteLineAsync(indent, $"else if ({value})", cancellationToken);
                await writer.WriteLineAsync(indent, "{", cancellationToken);
                await WriteStatementsAsync(writer, indent + 1, elseIfCodeStatement, cancellationToken);
                await writer.WriteLineAsync(indent, "}", cancellationToken);
                break;
            case ForCodeStatement forCodeStatement:
                variable = await GetStatementStringAsync(0, forCodeStatement.Variable, cancellationToken);
                var condition = await GetExpressionStringAsync(forCodeStatement.Condition, cancellationToken);
                var step = await GetExpressionStringAsync(forCodeStatement.Step, cancellationToken);
                await writer.WriteLineAsync(indent, $"for ({variable.Trim()}; {condition}; {step})", cancellationToken);
                await writer.WriteLineAsync(indent, "{", cancellationToken);
                await WriteStatementsAsync(writer, indent + 1, forCodeStatement, cancellationToken);
                await writer.WriteLineAsync(indent, "}", cancellationToken);
                break;
            case IfCodeStatement ifCodeStatement:
                value = await GetExpressionStringAsync(ifCodeStatement.Condition, cancellationToken);
                await writer.WriteLineAsync(indent, $"if ({value})", cancellationToken);
                await writer.WriteLineAsync(indent, "{", cancellationToken);
                await WriteStatementsAsync(writer, indent + 1, ifCodeStatement, cancellationToken);
                await writer.WriteLineAsync(indent, "}", cancellationToken);
                break;
            case SwitchCodeStatement switchCodeStatement:
                value = await GetExpressionStringAsync(switchCodeStatement.SwitchOn, cancellationToken);
                await writer.WriteLineAsync(indent, $"switch ({value})", cancellationToken);
                await writer.WriteLineAsync(indent, "{", cancellationToken);
                await WriteStatementsAsync(writer, indent + 1, switchCodeStatement, cancellationToken);
                await writer.WriteLineAsync(indent, "}", cancellationToken);
                break;
            case WhileCodeStatement whileCodeStatement:
                value = await GetExpressionStringAsync(whileCodeStatement.Condition, cancellationToken);
                await writer.WriteLineAsync(indent, $"while ({value})", cancellationToken);
                await writer.WriteLineAsync(indent, "{", cancellationToken);
                await WriteStatementsAsync(writer, indent + 1, whileCodeStatement, cancellationToken);
                await writer.WriteLineAsync(indent, "}", cancellationToken);
                break;
            case BreakStatement:
                await writer.WriteLineAsync(indent, "break;", cancellationToken);
                break;
            case CodeExpressionStatement codeExpressionStatement:
                value = await GetExpressionStringAsync(codeExpressionStatement.Expression, cancellationToken);
                await writer.WriteLineAsync(indent, $"{value};", cancellationToken);
                break;
            case ContinueStatement:
                await writer.WriteLineAsync(indent, "continue;", cancellationToken);
                break;
            case ReturnStatement returnStatement:
                if (returnStatement.ReturnValue is null)
                    await writer.WriteLineAsync(indent, "return;", cancellationToken);
                else
                {
                    value = await GetExpressionStringAsync(returnStatement.ReturnValue, cancellationToken);
                    await writer.WriteLineAsync(indent, $"return {value};", cancellationToken);
                }

                break;
            case VariableStatement variableStatement:
                value    = await GetExpressionStringAsync(variableStatement.InitialValue, cancellationToken);
                variable = VarIdent(variableStatement.Identifier);
                var type = TypeFor(variableStatement.Type);
                await writer.WriteLineAsync(indent, $"{type} {variable} = {value};", cancellationToken);
                break;
            case Function:
                throw new NotSupportedException("Cannot create a function in a function");
            // ReSharper disable once RedundantCaseLabel
            case CodeStatementHostBase:
            // ReSharper disable once RedundantCaseLabel
            case ICodeStatementsHost:
            default:
                throw new ArgumentOutOfRangeException(nameof(statement));
        }
    }

    private async Task<string> GetStatementStringAsync(
        int indent,
        ICodeStatement statement,
        CancellationToken cancellationToken)
    {
        await using var writer = new StringWriter();
        await WriteStatementAsync(writer, indent, statement, cancellationToken);
        return writer.ToString();
    }

    private async Task<string> GetExpressionStringAsync(ICodeExpression expression, CancellationToken cancellationToken)
    {
        await using var writer = new StringWriter();
        await WriteExpressionAsync(writer, expression, cancellationToken);
        return writer.ToString();
    }

    private async Task WriteExpressionAsync(
        TextWriter writer,
        ICodeExpression expression,
        CancellationToken cancellationToken)
    {
        switch (expression)
        {
            case AndExpression andExpression:
                await WriteExpressionAsync(writer, andExpression.Left, cancellationToken);
                await writer.WriteAsync(" && ", cancellationToken);
                await WriteExpressionAsync(writer, andExpression.Right, cancellationToken);
                break;
            case ArrayAccessExpression arrayAccessExpression:
                await WriteExpressionAsync(writer, arrayAccessExpression.Expression, cancellationToken);
                await writer.WriteAsync("[", cancellationToken);
                await WriteExpressionAsync(writer, arrayAccessExpression.Index, cancellationToken);
                await writer.WriteAsync("]", cancellationToken);
                break;
            case AssignExpression assignExpression:
                await WriteExpressionAsync(writer, assignExpression.Target, cancellationToken);
                await writer.WriteAsync(" = ", cancellationToken);
                await WriteExpressionAsync(writer, assignExpression.Value, cancellationToken);
                break;
            case ConditionalExpression conditionalExpression:
                await writer.WriteAsync("(", cancellationToken);
                await WriteExpressionAsync(writer, conditionalExpression.Condition, cancellationToken);
                await writer.WriteAsync(" ? ", cancellationToken);
                await WriteExpressionAsync(writer, conditionalExpression.OnTrue, cancellationToken);
                await writer.WriteAsync(" : ", cancellationToken);
                await WriteExpressionAsync(writer, conditionalExpression.OnFalse, cancellationToken);
                await writer.WriteAsync(")", cancellationToken);
                break;
            case DecrementExpression decrementExpression:
                await WriteExpressionAsync(writer, decrementExpression.Expression, cancellationToken);
                await writer.WriteAsync("--", cancellationToken);
                break;
            case EmptyValueExpression emptyValueExpression:
                switch (emptyValueExpression.Type)
                {
                    case EType.FileOffset:
                    case EType.Integer:
                    case EType.Size:
                        await writer.WriteAsync("0", cancellationToken);
                        break;
                    case EType.OptionalSize:
                        await writer.WriteAsync("null", cancellationToken);
                        break;
                    case EType.CharacterCollection:
                        await writer.WriteAsync("string.Empty", cancellationToken);
                        break;
                    case EType.Character:
                        await writer.WriteAsync("'\\0'", cancellationToken);
                        break;
                    case EType.Boolean:
                        await writer.WriteAsync("false", cancellationToken);
                        break;
                    case EType.Void:
                        throw new NotSupportedException("Cannot have an empty void value");
                    default:
                        throw new ArgumentOutOfRangeException();
                }

                break;
            case EqualExpression equalExpression:
                await WriteExpressionAsync(writer, equalExpression.Left, cancellationToken);
                await writer.WriteAsync(" == ", cancellationToken);
                await WriteExpressionAsync(writer, equalExpression.Right, cancellationToken);
                break;
            case FunctionCallExpression functionCallExpression:
                await writer.WriteAsync(FuncIdent(functionCallExpression.FunctionReference.Function.Identifier));
                await writer.WriteAsync("(");
                foreach (var (parameter, index) in functionCallExpression.Arguments.Indexed())
                {
                    if (index > 0)
                        await writer.WriteAsync(", ", cancellationToken);
                    await WriteExpressionAsync(writer, parameter, cancellationToken);
                }

                await writer.WriteAsync(")", cancellationToken);
                break;
            case GreaterThanExpression greaterThanExpression:
                await WriteExpressionAsync(writer, greaterThanExpression.Left, cancellationToken);
                await writer.WriteAsync(" > ", cancellationToken);
                await WriteExpressionAsync(writer, greaterThanExpression.Right, cancellationToken);
                break;
            case GreaterThanOrEqualExpression greaterThanOrEqualExpression:
                await WriteExpressionAsync(writer, greaterThanOrEqualExpression.Left, cancellationToken);
                await writer.WriteAsync(" >= ", cancellationToken);
                await WriteExpressionAsync(writer, greaterThanOrEqualExpression.Right, cancellationToken);
                break;
            case IncreaseExpression increaseExpression:
                await WriteExpressionAsync(writer, increaseExpression.Expression, cancellationToken);
                await writer.WriteAsync("++", cancellationToken);
                break;
            case LessThanExpression lessThanExpression:
                await WriteExpressionAsync(writer, lessThanExpression.Left, cancellationToken);
                await writer.WriteAsync(" < ", cancellationToken);
                await WriteExpressionAsync(writer, lessThanExpression.Right, cancellationToken);
                break;
            case LessThanOrEqualExpression lessThanOrEqualExpression:
                await WriteExpressionAsync(writer, lessThanOrEqualExpression.Left, cancellationToken);
                await writer.WriteAsync(" <= ", cancellationToken);
                await WriteExpressionAsync(writer, lessThanOrEqualExpression.Right, cancellationToken);
                break;
            case LogicalNotExpression logicalNotExpression:
                await writer.WriteAsync("!", cancellationToken);
                await WriteExpressionAsync(writer, logicalNotExpression.Expression, cancellationToken);
                break;
            case MinusExpression minusExpression:
                await WriteExpressionAsync(writer, minusExpression.Left, cancellationToken);
                await writer.WriteAsync(" - ", cancellationToken);
                await WriteExpressionAsync(writer, minusExpression.Right, cancellationToken);
                break;
            case NotEqualExpression notEqualExpression:
                await WriteExpressionAsync(writer, notEqualExpression.Left, cancellationToken);
                await writer.WriteAsync(" != ", cancellationToken);
                await WriteExpressionAsync(writer, notEqualExpression.Right, cancellationToken);
                break;
            case OrExpression orExpression:
                await WriteExpressionAsync(writer, orExpression.Left, cancellationToken);
                await writer.WriteAsync(" || ", cancellationToken);
                await WriteExpressionAsync(writer, orExpression.Right, cancellationToken);
                break;
            case PlusExpression plusExpression:
                await WriteExpressionAsync(writer, plusExpression.Left, cancellationToken);
                await writer.WriteAsync(" + ", cancellationToken);
                await WriteExpressionAsync(writer, plusExpression.Right, cancellationToken);
                break;
            case PropertyAccessExpression propertyAccessExpression:
                switch (propertyAccessExpression.Property)
                {
                    case EProperty.CharacterCollectionLength:
                        await WriteExpressionAsync(writer, propertyAccessExpression.Source, cancellationToken);
                        await writer.WriteAsync(".Length");
                        break;
                    case EProperty.HasValue:
                        await WriteExpressionAsync(writer, propertyAccessExpression.Source, cancellationToken);
                        await writer.WriteAsync(".HasValue");
                        break;
                    case EProperty.GetValue:
                        await WriteExpressionAsync(writer, propertyAccessExpression.Source, cancellationToken);
                        await writer.WriteAsync(".Value");
                        break;
                    case EProperty.Invalid:
                    default:
                        throw new ArgumentOutOfRangeException();
                }

                break;
            case ValueExpression valueExpression:
                switch (valueExpression.Value)
                {
                    case char c:
                        await writer.WriteAsync($"'{Escape(c)}'", cancellationToken);
                        break;
                    case string s:
                        await writer.WriteAsync($"'{Escape(s)}'", cancellationToken);
                        break;
                    case null:
                        await writer.WriteAsync($"default", cancellationToken);
                        break;
                    case bool flag:
                        await writer.WriteAsync(flag ? "true" : "false", cancellationToken);
                        break;
                    default:
                        await writer.WriteAsync(valueExpression.Value.ToString() ?? string.Empty, cancellationToken);
                        break;
                }
                break;
            case State state:
                await writer.WriteAsync(StateIdent(state.Identifier), cancellationToken);
                break;
            case VariableReference variableReference:
                await writer.WriteAsync(VarIdent(variableReference.VariableStatement.Identifier), cancellationToken);
                break;
            default:
                throw new ArgumentOutOfRangeException(nameof(expression));
        }
    }

    private string Escape(string s)
    {
        var builder = new StringBuilder(s.Length);
        foreach (var c in s)
        {
            builder.Append(Escape(c));
        }

        return builder.ToString();
    }
    private string Escape(char c)
    {
        return c switch
        {
            '\t' => "\\t",
            '\r' => "\\r",
            '\n' => "\\n",
            '\0' => "\\0",
           _ => c.ToString(),
        };
    }

    private static string FuncIdent(string identifier)
    {
        identifier = Sanitize(identifier);
        return $"{identifier[..1].ToUpper()}{identifier[1..]}";
    }

    private static string StateIdent(string identifier)
    {
        identifier = Sanitize(identifier);
        return $"_{identifier[..1].ToLower()}{identifier[1..]}";
    }

    private static string VarIdent(string identifier)
    {
        identifier = Sanitize(identifier);
        return $"{identifier[..1].ToLower()}{identifier[1..]}";
    }

    private static string Sanitize(string identifier)
    {
        var builder = new StringBuilder(identifier.Length);
        foreach (var c in identifier)
        {
            switch (c)
            {
                case >= 'a' and <= 'z':
                case >= 'A' and <= 'Z':
                case >= '0' and <= '9':
                case '_':
                    builder.Append(c);
                    break;
            }
        }

        return builder.ToString();
    }

    private static string TypeFor(EType stateType)
    {
        return stateType switch
        {
            EType.Void                => "void",
            EType.FileOffset          => "long",
            EType.Integer             => "int",
            EType.CharacterCollection => "string",
            EType.Size                => "int",
            EType.OptionalSize        => "int?",
            EType.Character           => "char",
            EType.Boolean             => "bool",
            _                         => throw new ArgumentOutOfRangeException(nameof(stateType), stateType, null)
        };
    }
}