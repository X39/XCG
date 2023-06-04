using System;
using JetBrains.Annotations;
using X39.Systems.XCG.Generators.Base.Contracts;
using X39.Systems.XCG.Generators.Base.Enums;
using X39.Systems.XCG.Generators.Base.Parts;
using X39.Systems.XCG.Generators.Base.Statements;
using X39.Systems.XCG.Generators.Base.Extensions;

namespace X39.Systems.XCG.Generators.Base;

internal class ResetData
{
    public VariableStatement? ColumnVariable;
    public VariableStatement? LineVariable;
    public VariableStatement? OffsetVariable;
    public VariableStatement? ContentsLengthVariable;
    public VariableStatement? ContentsVariable;
    public State? ColumnState;
    public State? LineState;
    public State? OffsetState;
    public State? ContentsLengthState;
    public State? ContentsState;
    
    

    public void PerformReset(ICodeStatementsHost host)
    {
        void Assign(VariableStatement? variableStatement, State? state)
        {
            if (variableStatement is null)
                throw new NullReferenceException("ResetData is not initialized.");
            if (state is null)
                throw new NullReferenceException("ResetData is not initialized.");
            host.AddExpression(state.Assign(variableStatement.Ref()));
        }
        Assign(ColumnVariable, ColumnState);
        Assign(LineVariable, LineState);
        Assign(OffsetVariable, OffsetState);
        Assign(ContentsLengthVariable, ContentsLengthState);
        Assign(ContentsVariable, ContentsState);
    }
    [Pure]
    public static ResetData Create(Group group, Function function)
    {
        // ReSharper disable RedundantAssignment
        void Variable(ref VariableStatement? columnVariable, ref State? columnState, string stateIdentifier, EType type)
            // ReSharper restore RedundantAssignment
        {
            columnState = group.State(stateIdentifier, type);
            columnVariable = function.AddVariable(
                Constants.VariablePrefixes.ResetHolder + stateIdentifier,
                type,
                columnState);
        }

        var o = new ResetData();
        Variable(ref o.ColumnVariable, ref o.ColumnState, Constants.States.ParsingColumn, EType.FileOffset);
        Variable(ref o.LineVariable, ref o.LineState, Constants.States.ParsingLine, EType.FileOffset);
        Variable(ref o.OffsetVariable, ref o.OffsetState, Constants.States.ParsingOffset, EType.FileOffset);
        Variable(ref o.ContentsLengthVariable, ref o.ContentsLengthState, Constants.States.ParsingContentsLength, EType.Size);
        Variable(ref o.ContentsVariable, ref o.ContentsState, Constants.States.ParsingContents, EType.CharacterCollection);
        return o;
    }
}