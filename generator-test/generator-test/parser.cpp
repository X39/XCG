#include "parser.hpp"
#include <iostream>

 yaoosl::parsing::instance::resetable::resetable(instance& ref): m_ref(ref)
{
    m_contents = ref.m_contents;
    m_file = ref.m_file;
    m_line = ref.m_line;
    m_column = ref.m_column;
    m_offset = ref.m_offset;
}
void yaoosl::parsing::instance::resetable::reset()
{
    m_ref.m_contents   = m_contents;
    m_ref.m_file       = m_file;
    m_ref.m_line       = m_line;
    m_ref.m_column     = m_column;
    m_ref.m_offset     = m_offset;
}
void yaoosl::parsing::instance::skip()
{
    while (m_contents.length() > m_offset)
    {
        char c = m_contents[m_offset];
        switch (c)
        {
            case '\r':
            case '\t':
            case ' ': m_column++; m_offset++; break;
            case '\n': m_line++; m_column = 1; m_offset++; break;
            default: return;
        }
    }
}
bool yaoosl::parsing::instance::next()
{
    if (m_contents.length() > m_offset)
    {
        char c = m_contents[m_offset];
        switch (c)
        {
            case '\r':
            case '\t':
            case ' ':
            default: m_column++; m_offset++; break;
            case '\n': m_line++; m_column = 1; m_offset++; break;
        }
        return true;
    }
    else
    {
        return false;
    }
}
char yaoosl::parsing::instance::current()
{
    if (m_contents.length() > m_offset)
    {
        return m_contents[m_offset];
    }
    else
    {
        return '\0';
    }
}
std::optional<size_t> yaoosl::parsing::instance::token_integer(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0')
    {
        if (('0' <= current() && current() <= '9'))
        {
            count2++;
            next();
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on integer", depth);
        return {};
    }
    auto resultVariable1 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable1) + " on integer").c_str(), depth);
    return resultVariable1;
}
std::optional<size_t> yaoosl::parsing::instance::token_scalar(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        std::optional<size_t> res3 = token_integer(depth + 1);
        if (res3.has_value())
        {
            count2++;
            for (size_t i = 0; i < res3; i++)
            {
                next();
            }
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on scalar", depth);
        return {};
    }
    size_t count4 = 0;
    while (current() != '\0' && count4 < 1)
    {
        if (current() == '.')
        {
            count4++;
            next();
            continue;
        }
        break;
    }
    if (count4 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on scalar", depth);
        return {};
    }
    size_t count5 = 0;
    while (current() != '\0' && count5 < 1)
    {
        std::optional<size_t> res6 = token_integer(depth + 1);
        if (res6.has_value())
        {
            count5++;
            for (size_t i = 0; i < res6; i++)
            {
                next();
            }
            continue;
        }
        break;
    }
    if (count5 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on scalar", depth);
        return {};
    }
    auto resultVariable2 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable2) + " on scalar").c_str(), depth);
    return resultVariable2;
}
std::optional<size_t> yaoosl::parsing::instance::token_slash(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == '/')
        {
            count2++;
            next();
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on slash", depth);
        return {};
    }
    auto resultVariable3 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable3) + " on slash").c_str(), depth);
    return resultVariable3;
}
std::optional<size_t> yaoosl::parsing::instance::token_star(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == '*')
        {
            count2++;
            next();
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on star", depth);
        return {};
    }
    auto resultVariable4 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable4) + " on star").c_str(), depth);
    return resultVariable4;
}
std::optional<size_t> yaoosl::parsing::instance::token_plus(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == '+')
        {
            count2++;
            next();
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on plus", depth);
        return {};
    }
    auto resultVariable5 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable5) + " on plus").c_str(), depth);
    return resultVariable5;
}
std::optional<size_t> yaoosl::parsing::instance::token_minus(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == '-')
        {
            count2++;
            next();
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on minus", depth);
        return {};
    }
    auto resultVariable6 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable6) + " on minus").c_str(), depth);
    return resultVariable6;
}
std::optional<size_t> yaoosl::parsing::instance::token_underscore(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == '_')
        {
            count2++;
            next();
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on underscore", depth);
        return {};
    }
    auto resultVariable7 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable7) + " on underscore").c_str(), depth);
    return resultVariable7;
}
std::optional<size_t> yaoosl::parsing::instance::token_ident(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (('a' <= current() && current() <= 'z'))
        {
            count2++;
            next();
            continue;
        }
        else if (('A' <= current() && current() <= 'Z'))
        {
            count2++;
            next();
            continue;
        }
        std::optional<size_t> res3 = token_underscore(depth + 1);
        if (res3.has_value())
        {
            count2++;
            for (size_t i = 0; i < res3; i++)
            {
                next();
            }
            continue;
        }
        std::optional<size_t> res4 = token_minus(depth + 1);
        if (res4.has_value())
        {
            count2++;
            for (size_t i = 0; i < res4; i++)
            {
                next();
            }
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on ident", depth);
        return {};
    }
    size_t count5 = 0;
    while (current() != '\0')
    {
        if (('a' <= current() && current() <= 'z'))
        {
            count5++;
            next();
            continue;
        }
        else if (('A' <= current() && current() <= 'Z'))
        {
            count5++;
            next();
            continue;
        }
        else if (('0' <= current() && current() <= '9'))
        {
            count5++;
            next();
            continue;
        }
        std::optional<size_t> res6 = token_underscore(depth + 1);
        if (res6.has_value())
        {
            count5++;
            for (size_t i = 0; i < res6; i++)
            {
                next();
            }
            continue;
        }
        std::optional<size_t> res7 = token_minus(depth + 1);
        if (res7.has_value())
        {
            count5++;
            for (size_t i = 0; i < res7; i++)
            {
                next();
            }
            continue;
        }
        break;
    }
    size_t count8 = 1;
    size_t loff9 = 0;
    while (current() != '\0' && count8 > 0)
    {
        if (m_offset >= 1 && m_contents[m_offset - 1] == '-')
        {
            break;
        }
        count8--;
    }
    if (count8 >= 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on ident", depth);
        return {};
    }
    auto resultVariable8 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable8) + " on ident").c_str(), depth);
    return resultVariable8;
}
std::optional<size_t> yaoosl::parsing::instance::token_string(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == '"')
        {
            count2++;
            next();
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on string", depth);
        return {};
    }
    size_t count3 = 0;
    while (current() != '\0')
    {
        if (current() != '"')
        {
            count3++;
            next();
            continue;
        }
        break;
    }
    size_t count4 = 0;
    while (current() != '\0' && count4 < 1)
    {
        if (current() == '"')
        {
            count4++;
            next();
            continue;
        }
        break;
    }
    if (count4 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on string", depth);
        return {};
    }
    auto resultVariable9 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable9) + " on string").c_str(), depth);
    return resultVariable9;
}
std::optional<size_t> yaoosl::parsing::instance::token__round_bracked_open(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == '(')
        {
            count2++;
            next();
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on @round-bracked-open", depth);
        return {};
    }
    auto resultVariable10 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable10) + " on @round-bracked-open").c_str(), depth);
    return resultVariable10;
}
std::optional<size_t> yaoosl::parsing::instance::token__round_bracked_close(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == ')')
        {
            count2++;
            next();
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on @round-bracked-close", depth);
        return {};
    }
    auto resultVariable11 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable11) + " on @round-bracked-close").c_str(), depth);
    return resultVariable11;
}
std::optional<size_t> yaoosl::parsing::instance::token__comma(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == ',')
        {
            count2++;
            next();
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on @comma", depth);
        return {};
    }
    auto resultVariable12 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable12) + " on @comma").c_str(), depth);
    return resultVariable12;
}
std::optional<size_t> yaoosl::parsing::instance::token__less_then_equal(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "<=";
        if (m_contents.length() - m_offset >= 2 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 2, str3, str3 + 2))
        {
            count2++;
            for (size_t i = 0; i < 2; i++)
            {
                next();
            }
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on @less-then-equal", depth);
        return {};
    }
    auto resultVariable13 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable13) + " on @less-then-equal").c_str(), depth);
    return resultVariable13;
}
std::optional<size_t> yaoosl::parsing::instance::token__less_then(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == '<')
        {
            count2++;
            next();
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on @less-then", depth);
        return {};
    }
    auto resultVariable14 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable14) + " on @less-then").c_str(), depth);
    return resultVariable14;
}
std::optional<size_t> yaoosl::parsing::instance::token__greater_then_equal(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = ">=";
        if (m_contents.length() - m_offset >= 2 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 2, str3, str3 + 2))
        {
            count2++;
            for (size_t i = 0; i < 2; i++)
            {
                next();
            }
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on @greater-then-equal", depth);
        return {};
    }
    auto resultVariable15 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable15) + " on @greater-then-equal").c_str(), depth);
    return resultVariable15;
}
std::optional<size_t> yaoosl::parsing::instance::token__greater_then(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == '>')
        {
            count2++;
            next();
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on @greater-then", depth);
        return {};
    }
    auto resultVariable16 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable16) + " on @greater-then").c_str(), depth);
    return resultVariable16;
}
std::optional<size_t> yaoosl::parsing::instance::token__and(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "and";
        if (m_contents.length() - m_offset >= 3 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 3, str3, str3 + 3))
        {
            count2++;
            for (size_t i = 0; i < 3; i++)
            {
                next();
            }
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on @and", depth);
        return {};
    }
    auto resultVariable17 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable17) + " on @and").c_str(), depth);
    return resultVariable17;
}
std::optional<size_t> yaoosl::parsing::instance::token__or(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "or";
        if (m_contents.length() - m_offset >= 2 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 2, str3, str3 + 2))
        {
            count2++;
            for (size_t i = 0; i < 2; i++)
            {
                next();
            }
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on @or", depth);
        return {};
    }
    auto resultVariable18 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable18) + " on @or").c_str(), depth);
    return resultVariable18;
}
std::optional<size_t> yaoosl::parsing::instance::token__equal(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == '=')
        {
            count2++;
            next();
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on @equal", depth);
        return {};
    }
    auto resultVariable19 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable19) + " on @equal").c_str(), depth);
    return resultVariable19;
}
std::optional<size_t> yaoosl::parsing::instance::token__return(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "return";
        if (m_contents.length() - m_offset >= 6 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 6, str3, str3 + 6))
        {
            count2++;
            for (size_t i = 0; i < 6; i++)
            {
                next();
            }
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on @return", depth);
        return {};
    }
    auto resultVariable20 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable20) + " on @return").c_str(), depth);
    return resultVariable20;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_80(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == ';')
        {
            count2++;
            next();
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on @auto-80", depth);
        return {};
    }
    auto resultVariable21 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable21) + " on @auto-80").c_str(), depth);
    return resultVariable21;
}
std::optional<size_t> yaoosl::parsing::instance::token__curly_bracked_open(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == '{')
        {
            count2++;
            next();
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on @curly-bracked-open", depth);
        return {};
    }
    auto resultVariable22 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable22) + " on @curly-bracked-open").c_str(), depth);
    return resultVariable22;
}
std::optional<size_t> yaoosl::parsing::instance::token__curly_bracked_close(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == '}')
        {
            count2++;
            next();
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on @curly-bracked-close", depth);
        return {};
    }
    auto resultVariable23 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable23) + " on @curly-bracked-close").c_str(), depth);
    return resultVariable23;
}
std::optional<size_t> yaoosl::parsing::instance::token__func(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "func";
        if (m_contents.length() - m_offset >= 4 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 4, str3, str3 + 4))
        {
            count2++;
            for (size_t i = 0; i < 4; i++)
            {
                next();
            }
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on @func", depth);
        return {};
    }
    auto resultVariable24 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable24) + " on @func").c_str(), depth);
    return resultVariable24;
}
std::optional<size_t> yaoosl::parsing::instance::token__while(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "while";
        if (m_contents.length() - m_offset >= 5 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 5, str3, str3 + 5))
        {
            count2++;
            for (size_t i = 0; i < 5; i++)
            {
                next();
            }
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on @while", depth);
        return {};
    }
    auto resultVariable25 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable25) + " on @while").c_str(), depth);
    return resultVariable25;
}
std::optional<size_t> yaoosl::parsing::instance::token__if(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "if";
        if (m_contents.length() - m_offset >= 2 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 2, str3, str3 + 2))
        {
            count2++;
            for (size_t i = 0; i < 2; i++)
            {
                next();
            }
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on @if", depth);
        return {};
    }
    auto resultVariable26 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable26) + " on @if").c_str(), depth);
    return resultVariable26;
}
std::optional<size_t> yaoosl::parsing::instance::token__else(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "else";
        if (m_contents.length() - m_offset >= 4 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 4, str3, str3 + 4))
        {
            count2++;
            for (size_t i = 0; i < 4; i++)
            {
                next();
            }
            continue;
        }
        break;
    }
    if (count2 < 1)
    {
        resetable1.reset();
        trace("Returning EmptyClosure on @else", depth);
        return {};
    }
    auto resultVariable27 = m_offset - resetable1.m_offset;
    resetable1.reset();
    trace((std::string("Returning ") + std::to_string(resultVariable27) + " on @else").c_str(), depth);
    return resultVariable27;
}
bool yaoosl::parsing::instance::m_ident_roundbrackedopen_28(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token_ident(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_ident_roundbrackedopen_28", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_ident_roundbrackedopen_28", depth);
        return false;
    }
    auto l4 = token__round_bracked_open(depth + 1);
    if (l4.has_value())
    {
        for (auto i5 = l4.value(); i5 != 0; i5--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_ident_roundbrackedopen_28", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_ident_roundbrackedopen_28", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_ident_roundbrackedopen_28", depth);
        return true;
    }
    resetable1.reset();
    auto val6 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->method = val6;
    skip();
    auto l8 = token__round_bracked_open(depth + 1).value();
    for (;l8 != 0; l8--)
    {
        next();
    }
    skip();
    trace("Returning true on m_ident_roundbrackedopen_28", depth);
    return true;
}
bool yaoosl::parsing::instance::m_expression_29(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_expression(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expression_29", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expression_29", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_expression_29", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_expression(depth + 1);
    actual->args.push_back(val2);
    skip();
    trace("Returning true on m_expression_29", depth);
    return true;
}
bool yaoosl::parsing::instance::m_comma_expression_30(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__comma(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_comma_expression_30", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_comma_expression_30", depth);
        return false;
    }
    if (p_can_expression(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_comma_expression_30", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_comma_expression_30", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_comma_expression_30", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_expression(depth + 1);
    actual->args.push_back(val6);
    skip();
    trace("Returning true on m_comma_expression_30", depth);
    return true;
}
bool yaoosl::parsing::instance::m_comma_31(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__comma(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_comma_31", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_comma_31", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_comma_31", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    trace("Returning true on m_comma_31", depth);
    return true;
}
bool yaoosl::parsing::instance::alternatives32(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_comma_expression_30(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives32", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_comma_expression_30(false, actual, state, depth + 1);
            trace("Returning true on alternatives32", depth);
            return true;
        }
    }
    else if (m_comma_31(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives32", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_comma_31(false, actual, state, depth + 1);
            trace("Returning true on alternatives32", depth);
            return true;
        }
    }
    else if (!is_can)
    {
        report("Failed to match one of the following: { ,, expression, , }", depth);
    }
    resetable1.reset();
    trace("Returning false on alternatives32", depth);
    return false;
}
bool yaoosl::parsing::instance::m_roundbrackedclose_33(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__round_bracked_close(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_roundbrackedclose_33", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_roundbrackedclose_33", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_roundbrackedclose_33", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    trace("Returning true on m_roundbrackedclose_33", depth);
    return true;
}
bool yaoosl::parsing::instance::while34_35(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_roundbrackedclose_33(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives32(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_33(true, actual, state, depth + 1);
            resetable2.reset();
        }
        trace("Returning true on while34_35", depth);
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives32(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives32(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_33(true, actual, state, depth + 1);
            resetable2.reset();
        }
        trace("Returning true on while34_35", depth);
        return true;
    }
}
bool yaoosl::parsing::instance::m_expression_36(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_expression(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expression_36", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expression_36", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_expression_36", depth);
        return true;
    }
    resetable1.reset();
    p_match_expression(depth + 1);
    skip();
    trace("Returning true on m_expression_36", depth);
    return true;
}
bool yaoosl::parsing::instance::if37_38(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_expression_36(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_expression_29(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                trace("Returning false on XCG.Parsing.Statements.Match", depth);
                return false;
            }
            else
            {
                report("Failed to match { $ref: expression (XCG.Parsing.Production) }", depth);
                trace("Returning false on XCG.Parsing.Statements.Match", depth);
                return false;
            }
            while34_35(true, actual, state, depth + 1);
            trace("Returning true on if37_38", depth);
            return true;
        }
        trace("Returning true on if37_38", depth);
        return true;
    }
    else
    {
        if (cond2)
        {
            if (m_expression_29(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                trace("Returning false on XCG.Parsing.Statements.Match", depth);
                return false;
            }
            else
            {
                report("Failed to match { $ref: expression (XCG.Parsing.Production) }", depth);
                trace("Returning false on XCG.Parsing.Statements.Match", depth);
                return false;
            }
            while34_35(false, actual, state, depth + 1);
            trace("Returning true on if37_38", depth);
            return true;
        }
        trace("Returning true on if37_38", depth);
        return true;
    }
}
bool yaoosl::parsing::instance::m_roundbrackedclose_39(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__round_bracked_close(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_roundbrackedclose_39", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_roundbrackedclose_39", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_roundbrackedclose_39", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    trace("Returning true on m_roundbrackedclose_39", depth);
    return true;
}
bool yaoosl::parsing::instance::p_can_call(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::call> fake;
    call_state state;
    if (!m_ident_roundbrackedopen_28(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on call", depth);
        return false;
    }
    else if (!if37_38(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on call", depth);
        return false;
    }
    else if (!m_roundbrackedclose_39(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on call", depth);
        return false;
    }
    trace("Returning true on call", depth);
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::call> yaoosl::parsing::instance::p_match_call(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::call>();
    std::shared_ptr<yaoosl::parsing::instance::call> fake;
    call_state state;
    resetable resetable2(*this);
    if (m_ident_roundbrackedopen_28(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_ident_roundbrackedopen_28(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (if37_38(true, fake, state, depth + 1))
    {
        resetable3.reset();
        if37_38(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (m_roundbrackedclose_39(true, fake, state, depth + 1))
    {
        resetable4.reset();
        m_roundbrackedclose_39(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_call_40(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_call(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_call_40", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_call_40", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_call_40", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_call(depth + 1);
    actual->value = val2;
    skip();
    trace("Returning true on m_call_40", depth);
    return true;
}
bool yaoosl::parsing::instance::m_roundbrackedopen_statement_roundbrackedclose_41(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__round_bracked_open(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_roundbrackedopen_statement_roundbrackedclose_41", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_roundbrackedopen_statement_roundbrackedclose_41", depth);
        return false;
    }
    if (p_can_statement(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_roundbrackedopen_statement_roundbrackedclose_41", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_roundbrackedopen_statement_roundbrackedclose_41", depth);
        return false;
    }
    auto l4 = token__round_bracked_close(depth + 1);
    if (l4.has_value())
    {
        for (auto i5 = l4.value(); i5 != 0; i5--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_roundbrackedopen_statement_roundbrackedclose_41", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_roundbrackedopen_statement_roundbrackedclose_41", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_roundbrackedopen_statement_roundbrackedclose_41", depth);
        return true;
    }
    resetable1.reset();
    auto l7 = token__round_bracked_open(depth + 1).value();
    for (;l7 != 0; l7--)
    {
        next();
    }
    skip();
    auto val8 = p_match_statement(depth + 1);
    actual->value = val8;
    skip();
    auto l10 = token__round_bracked_close(depth + 1).value();
    for (;l10 != 0; l10--)
    {
        next();
    }
    skip();
    trace("Returning true on m_roundbrackedopen_statement_roundbrackedclose_41", depth);
    return true;
}
bool yaoosl::parsing::instance::m_scalar_42(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token_scalar(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_scalar_42", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_scalar_42", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_scalar_42", depth);
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_scalar(depth + 1).value(), tok::SCALAR);
    actual->value = val4;
    skip();
    trace("Returning true on m_scalar_42", depth);
    return true;
}
bool yaoosl::parsing::instance::m_string_43(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token_string(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_string_43", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_string_43", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_string_43", depth);
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_string(depth + 1).value(), tok::STRING);
    actual->value = val4;
    skip();
    trace("Returning true on m_string_43", depth);
    return true;
}
bool yaoosl::parsing::instance::m_integer_44(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token_integer(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_integer_44", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_integer_44", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_integer_44", depth);
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_integer(depth + 1).value(), tok::INTEGER);
    actual->value = val4;
    skip();
    trace("Returning true on m_integer_44", depth);
    return true;
}
bool yaoosl::parsing::instance::m_ident_45(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token_ident(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_ident_45", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_ident_45", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_ident_45", depth);
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->value = val4;
    skip();
    trace("Returning true on m_ident_45", depth);
    return true;
}
bool yaoosl::parsing::instance::alternatives46(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_call_40(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives46", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_call_40(false, actual, state, depth + 1);
            trace("Returning true on alternatives46", depth);
            return true;
        }
    }
    else if (m_roundbrackedopen_statement_roundbrackedclose_41(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives46", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_roundbrackedopen_statement_roundbrackedclose_41(false, actual, state, depth + 1);
            trace("Returning true on alternatives46", depth);
            return true;
        }
    }
    else if (m_scalar_42(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives46", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_scalar_42(false, actual, state, depth + 1);
            trace("Returning true on alternatives46", depth);
            return true;
        }
    }
    else if (m_string_43(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives46", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_string_43(false, actual, state, depth + 1);
            trace("Returning true on alternatives46", depth);
            return true;
        }
    }
    else if (m_integer_44(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives46", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_integer_44(false, actual, state, depth + 1);
            trace("Returning true on alternatives46", depth);
            return true;
        }
    }
    else if (m_ident_45(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives46", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_ident_45(false, actual, state, depth + 1);
            trace("Returning true on alternatives46", depth);
            return true;
        }
    }
    resetable1.reset();
    trace("Returning false on alternatives46", depth);
    return false;
}
bool yaoosl::parsing::instance::p_can_exp_nullar(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_nullar> fake;
    exp_nullar_state state;
    if (!alternatives46(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on exp-nullar", depth);
        return false;
    }
    trace("Returning true on exp-nullar", depth);
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::exp_nullar> yaoosl::parsing::instance::p_match_exp_nullar(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_nullar>();
    std::shared_ptr<yaoosl::parsing::instance::exp_nullar> fake;
    exp_nullar_state state;
    resetable resetable2(*this);
    if (alternatives46(true, fake, state, depth + 1))
    {
        resetable2.reset();
        alternatives46(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_ident_equal_expression_47(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_assignment>& actual, yaoosl::parsing::instance::exp_assignment_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token_ident(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_ident_equal_expression_47", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_ident_equal_expression_47", depth);
        return false;
    }
    auto l4 = token__equal(depth + 1);
    if (l4.has_value())
    {
        for (auto i5 = l4.value(); i5 != 0; i5--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_ident_equal_expression_47", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_ident_equal_expression_47", depth);
        return false;
    }
    if (p_can_expression(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_ident_equal_expression_47", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_ident_equal_expression_47", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_ident_equal_expression_47", depth);
        return true;
    }
    resetable1.reset();
    auto val6 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->name = val6;
    skip();
    auto l8 = token__equal(depth + 1).value();
    for (;l8 != 0; l8--)
    {
        next();
    }
    skip();
    auto val9 = p_match_expression(depth + 1);
    actual->value = val9;
    skip();
    trace("Returning true on m_ident_equal_expression_47", depth);
    return true;
}
bool yaoosl::parsing::instance::p_can_exp_assignment(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_assignment> fake;
    exp_assignment_state state;
    if (!m_ident_equal_expression_47(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on exp-assignment", depth);
        return false;
    }
    trace("Returning true on exp-assignment", depth);
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::exp_assignment> yaoosl::parsing::instance::p_match_exp_assignment(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_assignment>();
    std::shared_ptr<yaoosl::parsing::instance::exp_assignment> fake;
    exp_assignment_state state;
    resetable resetable2(*this);
    if (m_ident_equal_expression_47(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_ident_equal_expression_47(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_return_expor_48(bool is_can, std::shared_ptr<yaoosl::parsing::instance::return_statement>& actual, yaoosl::parsing::instance::return_statement_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__return(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_return_expor_48", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_return_expor_48", depth);
        return false;
    }
    if (lr_can_exp_or(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_return_expor_48", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_return_expor_48", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_return_expor_48", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__return(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_or(depth + 1);
    actual->expression = val6;
    skip();
    trace("Returning true on m_return_expor_48", depth);
    return true;
}
bool yaoosl::parsing::instance::p_can_return_statement(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::return_statement> fake;
    return_statement_state state;
    if (!m_return_expor_48(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on return-statement", depth);
        return false;
    }
    trace("Returning true on return-statement", depth);
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::return_statement> yaoosl::parsing::instance::p_match_return_statement(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::return_statement>();
    std::shared_ptr<yaoosl::parsing::instance::return_statement> fake;
    return_statement_state state;
    resetable resetable2(*this);
    if (m_return_expor_48(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_return_expor_48(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expassignment_49(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expression>& actual, yaoosl::parsing::instance::expression_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_exp_assignment(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expassignment_49", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expassignment_49", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_expassignment_49", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_exp_assignment(depth + 1);
    actual->expression = val2;
    skip();
    trace("Returning true on m_expassignment_49", depth);
    return true;
}
bool yaoosl::parsing::instance::m_expor_50(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expression>& actual, yaoosl::parsing::instance::expression_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_exp_or(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expor_50", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expor_50", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_expor_50", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_exp_or(depth + 1);
    actual->expression = val2;
    skip();
    trace("Returning true on m_expor_50", depth);
    return true;
}
bool yaoosl::parsing::instance::alternatives51(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expression>& actual, yaoosl::parsing::instance::expression_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_expassignment_49(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives51", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_expassignment_49(false, actual, state, depth + 1);
            trace("Returning true on alternatives51", depth);
            return true;
        }
    }
    else if (m_expor_50(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives51", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_expor_50(false, actual, state, depth + 1);
            trace("Returning true on alternatives51", depth);
            return true;
        }
    }
    resetable1.reset();
    trace("Returning false on alternatives51", depth);
    return false;
}
bool yaoosl::parsing::instance::p_can_expression(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::expression> fake;
    expression_state state;
    if (!alternatives51(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on expression", depth);
        return false;
    }
    trace("Returning true on expression", depth);
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::expression> yaoosl::parsing::instance::p_match_expression(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::expression>();
    std::shared_ptr<yaoosl::parsing::instance::expression> fake;
    expression_state state;
    resetable resetable2(*this);
    if (alternatives51(true, fake, state, depth + 1))
    {
        resetable2.reset();
        alternatives51(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_returnstatement_auto80_52(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_return_statement(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_returnstatement_auto80_52", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_returnstatement_auto80_52", depth);
        return false;
    }
    auto l2 = token__auto_80(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_returnstatement_auto80_52", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_returnstatement_auto80_52", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_returnstatement_auto80_52", depth);
        return true;
    }
    resetable1.reset();
    auto val4 = p_match_return_statement(depth + 1);
    actual->expression = val4;
    skip();
    auto l6 = token__auto_80(depth + 1).value();
    for (;l6 != 0; l6--)
    {
        next();
    }
    skip();
    trace("Returning true on m_returnstatement_auto80_52", depth);
    return true;
}
bool yaoosl::parsing::instance::m_expression_auto80_53(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_expression(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expression_auto80_53", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expression_auto80_53", depth);
        return false;
    }
    auto l2 = token__auto_80(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expression_auto80_53", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expression_auto80_53", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_expression_auto80_53", depth);
        return true;
    }
    resetable1.reset();
    auto val4 = p_match_expression(depth + 1);
    actual->expression = val4;
    skip();
    auto l6 = token__auto_80(depth + 1).value();
    for (;l6 != 0; l6--)
    {
        next();
    }
    skip();
    trace("Returning true on m_expression_auto80_53", depth);
    return true;
}
bool yaoosl::parsing::instance::m_auto80_54(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__auto_80(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_auto80_54", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_auto80_54", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_auto80_54", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__auto_80(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    trace("Returning true on m_auto80_54", depth);
    return true;
}
bool yaoosl::parsing::instance::alternatives55(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_returnstatement_auto80_52(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives55", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_returnstatement_auto80_52(false, actual, state, depth + 1);
            trace("Returning true on alternatives55", depth);
            return true;
        }
    }
    else if (m_expression_auto80_53(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives55", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_expression_auto80_53(false, actual, state, depth + 1);
            trace("Returning true on alternatives55", depth);
            return true;
        }
    }
    else if (m_auto80_54(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives55", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_auto80_54(false, actual, state, depth + 1);
            trace("Returning true on alternatives55", depth);
            return true;
        }
    }
    resetable1.reset();
    trace("Returning false on alternatives55", depth);
    return false;
}
bool yaoosl::parsing::instance::p_can_statement(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::statement> fake;
    statement_state state;
    if (!alternatives55(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on statement", depth);
        return false;
    }
    trace("Returning true on statement", depth);
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::statement> yaoosl::parsing::instance::p_match_statement(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::statement>();
    std::shared_ptr<yaoosl::parsing::instance::statement> fake;
    statement_state state;
    resetable resetable2(*this);
    if (alternatives55(true, fake, state, depth + 1))
    {
        resetable2.reset();
        alternatives55(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_ident_56(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function_arg>& actual, yaoosl::parsing::instance::function_arg_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token_ident(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_ident_56", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_ident_56", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_ident_56", depth);
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->name = val4;
    skip();
    trace("Returning true on m_ident_56", depth);
    return true;
}
bool yaoosl::parsing::instance::p_can_function_arg(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::function_arg> fake;
    function_arg_state state;
    if (!m_ident_56(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on function-arg", depth);
        return false;
    }
    trace("Returning true on function-arg", depth);
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::function_arg> yaoosl::parsing::instance::p_match_function_arg(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::function_arg>();
    std::shared_ptr<yaoosl::parsing::instance::function_arg> fake;
    function_arg_state state;
    resetable resetable2(*this);
    if (m_ident_56(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_ident_56(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_curlybrackedopen_57(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__curly_bracked_open(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_curlybrackedopen_57", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_curlybrackedopen_57", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_curlybrackedopen_57", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_open(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    trace("Returning true on m_curlybrackedopen_57", depth);
    return true;
}
bool yaoosl::parsing::instance::m_controlstructure_58(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_control_structure(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_controlstructure_58", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_controlstructure_58", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_controlstructure_58", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_control_structure(depth + 1);
    actual->body.push_back(val2);
    skip();
    trace("Returning true on m_controlstructure_58", depth);
    return true;
}
bool yaoosl::parsing::instance::m_statement_59(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_statement(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_statement_59", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_statement_59", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_statement_59", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_statement(depth + 1);
    actual->body.push_back(val2);
    skip();
    trace("Returning true on m_statement_59", depth);
    return true;
}
bool yaoosl::parsing::instance::alternatives60(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_controlstructure_58(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives60", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_controlstructure_58(false, actual, state, depth + 1);
            trace("Returning true on alternatives60", depth);
            return true;
        }
    }
    else if (m_statement_59(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives60", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_statement_59(false, actual, state, depth + 1);
            trace("Returning true on alternatives60", depth);
            return true;
        }
    }
    else if (!is_can)
    {
        report("Failed to match one of the following: { control-structure, statement }", depth);
    }
    resetable1.reset();
    trace("Returning false on alternatives60", depth);
    return false;
}
bool yaoosl::parsing::instance::m_curlybrackedclose_61(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__curly_bracked_close(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_curlybrackedclose_61", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_curlybrackedclose_61", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_curlybrackedclose_61", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    trace("Returning true on m_curlybrackedclose_61", depth);
    return true;
}
bool yaoosl::parsing::instance::while62_63(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_curlybrackedclose_61(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives60(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_61(true, actual, state, depth + 1);
            resetable2.reset();
        }
        trace("Returning true on while62_63", depth);
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives60(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives60(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_61(true, actual, state, depth + 1);
            resetable2.reset();
        }
        trace("Returning true on while62_63", depth);
        return true;
    }
}
bool yaoosl::parsing::instance::m_curlybrackedclose_64(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__curly_bracked_close(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_curlybrackedclose_64", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_curlybrackedclose_64", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_curlybrackedclose_64", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    trace("Returning true on m_curlybrackedclose_64", depth);
    return true;
}
bool yaoosl::parsing::instance::p_can_scope(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::scope> fake;
    scope_state state;
    if (!m_curlybrackedopen_57(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on scope", depth);
        return false;
    }
    else if (!while62_63(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on scope", depth);
        return false;
    }
    else if (!m_curlybrackedclose_64(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on scope", depth);
        return false;
    }
    trace("Returning true on scope", depth);
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::scope> yaoosl::parsing::instance::p_match_scope(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::scope>();
    std::shared_ptr<yaoosl::parsing::instance::scope> fake;
    scope_state state;
    resetable resetable2(*this);
    if (m_curlybrackedopen_57(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_curlybrackedopen_57(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (while62_63(true, fake, state, depth + 1))
    {
        resetable3.reset();
        while62_63(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (m_curlybrackedclose_64(true, fake, state, depth + 1))
    {
        resetable4.reset();
        m_curlybrackedclose_64(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_func_ident_roundbrackedopen_65(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__func(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_func_ident_roundbrackedopen_65", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_func_ident_roundbrackedopen_65", depth);
        return false;
    }
    auto l4 = token_ident(depth + 1);
    if (l4.has_value())
    {
        for (auto i5 = l4.value(); i5 != 0; i5--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_func_ident_roundbrackedopen_65", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_func_ident_roundbrackedopen_65", depth);
        return false;
    }
    auto l6 = token__round_bracked_open(depth + 1);
    if (l6.has_value())
    {
        for (auto i7 = l6.value(); i7 != 0; i7--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_func_ident_roundbrackedopen_65", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_func_ident_roundbrackedopen_65", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_func_ident_roundbrackedopen_65", depth);
        return true;
    }
    resetable1.reset();
    auto l9 = token__func(depth + 1).value();
    for (;l9 != 0; l9--)
    {
        next();
    }
    skip();
    auto val10 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->name = val10;
    skip();
    auto l12 = token__round_bracked_open(depth + 1).value();
    for (;l12 != 0; l12--)
    {
        next();
    }
    skip();
    trace("Returning true on m_func_ident_roundbrackedopen_65", depth);
    return true;
}
bool yaoosl::parsing::instance::m_functionarg_66(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_function_arg(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_functionarg_66", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_functionarg_66", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_functionarg_66", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_function_arg(depth + 1);
    actual->args.push_back(val2);
    skip();
    trace("Returning true on m_functionarg_66", depth);
    return true;
}
bool yaoosl::parsing::instance::m_comma_functionarg_67(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__comma(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_comma_functionarg_67", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_comma_functionarg_67", depth);
        return false;
    }
    if (p_can_function_arg(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_comma_functionarg_67", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_comma_functionarg_67", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_comma_functionarg_67", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_function_arg(depth + 1);
    actual->args.push_back(val6);
    skip();
    trace("Returning true on m_comma_functionarg_67", depth);
    return true;
}
bool yaoosl::parsing::instance::m_roundbrackedclose_68(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__round_bracked_close(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_roundbrackedclose_68", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_roundbrackedclose_68", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_roundbrackedclose_68", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    trace("Returning true on m_roundbrackedclose_68", depth);
    return true;
}
bool yaoosl::parsing::instance::while69_70(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_roundbrackedclose_68(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            if (m_comma_functionarg_67(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                trace("Returning false on XCG.Parsing.Statements.Match", depth);
                return false;
            }
            else
            {
                report("Failed to match { $ref: , ({ Token: , (,)}), $ref: function-arg (XCG.Parsing.Production) }", depth);
                trace("Returning false on XCG.Parsing.Statements.Match", depth);
                return false;
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_68(true, actual, state, depth + 1);
            resetable2.reset();
        }
        trace("Returning true on while69_70", depth);
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (m_comma_functionarg_67(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                trace("Returning false on XCG.Parsing.Statements.Match", depth);
                return false;
            }
            else
            {
                report("Failed to match { $ref: , ({ Token: , (,)}), $ref: function-arg (XCG.Parsing.Production) }", depth);
                trace("Returning false on XCG.Parsing.Statements.Match", depth);
                return false;
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_68(true, actual, state, depth + 1);
            resetable2.reset();
        }
        trace("Returning true on while69_70", depth);
        return true;
    }
}
bool yaoosl::parsing::instance::m_functionarg_71(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_function_arg(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_functionarg_71", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_functionarg_71", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_functionarg_71", depth);
        return true;
    }
    resetable1.reset();
    p_match_function_arg(depth + 1);
    skip();
    trace("Returning true on m_functionarg_71", depth);
    return true;
}
bool yaoosl::parsing::instance::if72_73(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_functionarg_71(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_functionarg_66(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                trace("Returning false on XCG.Parsing.Statements.Match", depth);
                return false;
            }
            else
            {
                report("Failed to match { $ref: function-arg (XCG.Parsing.Production) }", depth);
                trace("Returning false on XCG.Parsing.Statements.Match", depth);
                return false;
            }
            while69_70(true, actual, state, depth + 1);
            trace("Returning true on if72_73", depth);
            return true;
        }
        trace("Returning true on if72_73", depth);
        return true;
    }
    else
    {
        if (cond2)
        {
            if (m_functionarg_66(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                trace("Returning false on XCG.Parsing.Statements.Match", depth);
                return false;
            }
            else
            {
                report("Failed to match { $ref: function-arg (XCG.Parsing.Production) }", depth);
                trace("Returning false on XCG.Parsing.Statements.Match", depth);
                return false;
            }
            while69_70(false, actual, state, depth + 1);
            trace("Returning true on if72_73", depth);
            return true;
        }
        trace("Returning true on if72_73", depth);
        return true;
    }
}
bool yaoosl::parsing::instance::m_roundbrackedclose_scope_74(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__round_bracked_close(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_roundbrackedclose_scope_74", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_roundbrackedclose_scope_74", depth);
        return false;
    }
    if (p_can_scope(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_roundbrackedclose_scope_74", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_roundbrackedclose_scope_74", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_roundbrackedclose_scope_74", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_scope(depth + 1);
    actual->body = val6;
    skip();
    trace("Returning true on m_roundbrackedclose_scope_74", depth);
    return true;
}
bool yaoosl::parsing::instance::p_can_function(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::function> fake;
    function_state state;
    if (!m_func_ident_roundbrackedopen_65(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on function", depth);
        return false;
    }
    else if (!if72_73(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on function", depth);
        return false;
    }
    else if (!m_roundbrackedclose_scope_74(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on function", depth);
        return false;
    }
    trace("Returning true on function", depth);
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::function> yaoosl::parsing::instance::p_match_function(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::function>();
    std::shared_ptr<yaoosl::parsing::instance::function> fake;
    function_state state;
    resetable resetable2(*this);
    if (m_func_ident_roundbrackedopen_65(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_func_ident_roundbrackedopen_65(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (if72_73(true, fake, state, depth + 1))
    {
        resetable3.reset();
        if72_73(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (m_roundbrackedclose_scope_74(true, fake, state, depth + 1))
    {
        resetable4.reset();
        m_roundbrackedclose_scope_74(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_while_roundbrackedopen_expression_roundbrackedclose_75(bool is_can, std::shared_ptr<yaoosl::parsing::instance::while_loop>& actual, yaoosl::parsing::instance::while_loop_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__while(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_while_roundbrackedopen_expression_roundbrackedclose_75", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_while_roundbrackedopen_expression_roundbrackedclose_75", depth);
        return false;
    }
    auto l4 = token__round_bracked_open(depth + 1);
    if (l4.has_value())
    {
        for (auto i5 = l4.value(); i5 != 0; i5--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_while_roundbrackedopen_expression_roundbrackedclose_75", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_while_roundbrackedopen_expression_roundbrackedclose_75", depth);
        return false;
    }
    if (p_can_expression(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_while_roundbrackedopen_expression_roundbrackedclose_75", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_while_roundbrackedopen_expression_roundbrackedclose_75", depth);
        return false;
    }
    auto l6 = token__round_bracked_close(depth + 1);
    if (l6.has_value())
    {
        for (auto i7 = l6.value(); i7 != 0; i7--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_while_roundbrackedopen_expression_roundbrackedclose_75", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_while_roundbrackedopen_expression_roundbrackedclose_75", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_while_roundbrackedopen_expression_roundbrackedclose_75", depth);
        return true;
    }
    resetable1.reset();
    auto l9 = token__while(depth + 1).value();
    for (;l9 != 0; l9--)
    {
        next();
    }
    skip();
    auto l11 = token__round_bracked_open(depth + 1).value();
    for (;l11 != 0; l11--)
    {
        next();
    }
    skip();
    auto val12 = p_match_expression(depth + 1);
    actual->condition = val12;
    skip();
    auto l14 = token__round_bracked_close(depth + 1).value();
    for (;l14 != 0; l14--)
    {
        next();
    }
    skip();
    trace("Returning true on m_while_roundbrackedopen_expression_roundbrackedclose_75", depth);
    return true;
}
bool yaoosl::parsing::instance::m_scope_76(bool is_can, std::shared_ptr<yaoosl::parsing::instance::while_loop>& actual, yaoosl::parsing::instance::while_loop_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_scope(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_scope_76", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_scope_76", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_scope_76", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_scope(depth + 1);
    actual->body = val2;
    skip();
    trace("Returning true on m_scope_76", depth);
    return true;
}
bool yaoosl::parsing::instance::m_controlstructure_77(bool is_can, std::shared_ptr<yaoosl::parsing::instance::while_loop>& actual, yaoosl::parsing::instance::while_loop_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_control_structure(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_controlstructure_77", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_controlstructure_77", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_controlstructure_77", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_control_structure(depth + 1);
    actual->body = val2;
    skip();
    trace("Returning true on m_controlstructure_77", depth);
    return true;
}
bool yaoosl::parsing::instance::m_statement_78(bool is_can, std::shared_ptr<yaoosl::parsing::instance::while_loop>& actual, yaoosl::parsing::instance::while_loop_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_statement(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_statement_78", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_statement_78", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_statement_78", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_statement(depth + 1);
    actual->body = val2;
    skip();
    trace("Returning true on m_statement_78", depth);
    return true;
}
bool yaoosl::parsing::instance::alternatives79(bool is_can, std::shared_ptr<yaoosl::parsing::instance::while_loop>& actual, yaoosl::parsing::instance::while_loop_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_scope_76(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives79", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_scope_76(false, actual, state, depth + 1);
            trace("Returning true on alternatives79", depth);
            return true;
        }
    }
    else if (m_controlstructure_77(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives79", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_controlstructure_77(false, actual, state, depth + 1);
            trace("Returning true on alternatives79", depth);
            return true;
        }
    }
    else if (m_statement_78(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives79", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_statement_78(false, actual, state, depth + 1);
            trace("Returning true on alternatives79", depth);
            return true;
        }
    }
    resetable1.reset();
    trace("Returning false on alternatives79", depth);
    return false;
}
bool yaoosl::parsing::instance::p_can_while_loop(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::while_loop> fake;
    while_loop_state state;
    if (!m_while_roundbrackedopen_expression_roundbrackedclose_75(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on while-loop", depth);
        return false;
    }
    else if (!alternatives79(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on while-loop", depth);
        return false;
    }
    trace("Returning true on while-loop", depth);
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::while_loop> yaoosl::parsing::instance::p_match_while_loop(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::while_loop>();
    std::shared_ptr<yaoosl::parsing::instance::while_loop> fake;
    while_loop_state state;
    resetable resetable2(*this);
    if (m_while_roundbrackedopen_expression_roundbrackedclose_75(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_while_roundbrackedopen_expression_roundbrackedclose_75(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (alternatives79(true, fake, state, depth + 1))
    {
        resetable3.reset();
        alternatives79(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_if_roundbrackedopen_expression_roundbrackedclose_80(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__if(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_if_roundbrackedopen_expression_roundbrackedclose_80", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_if_roundbrackedopen_expression_roundbrackedclose_80", depth);
        return false;
    }
    auto l4 = token__round_bracked_open(depth + 1);
    if (l4.has_value())
    {
        for (auto i5 = l4.value(); i5 != 0; i5--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_if_roundbrackedopen_expression_roundbrackedclose_80", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_if_roundbrackedopen_expression_roundbrackedclose_80", depth);
        return false;
    }
    if (p_can_expression(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_if_roundbrackedopen_expression_roundbrackedclose_80", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_if_roundbrackedopen_expression_roundbrackedclose_80", depth);
        return false;
    }
    auto l6 = token__round_bracked_close(depth + 1);
    if (l6.has_value())
    {
        for (auto i7 = l6.value(); i7 != 0; i7--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_if_roundbrackedopen_expression_roundbrackedclose_80", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_if_roundbrackedopen_expression_roundbrackedclose_80", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_if_roundbrackedopen_expression_roundbrackedclose_80", depth);
        return true;
    }
    resetable1.reset();
    auto l9 = token__if(depth + 1).value();
    for (;l9 != 0; l9--)
    {
        next();
    }
    skip();
    auto l11 = token__round_bracked_open(depth + 1).value();
    for (;l11 != 0; l11--)
    {
        next();
    }
    skip();
    auto val12 = p_match_expression(depth + 1);
    actual->condition = val12;
    skip();
    auto l14 = token__round_bracked_close(depth + 1).value();
    for (;l14 != 0; l14--)
    {
        next();
    }
    skip();
    trace("Returning true on m_if_roundbrackedopen_expression_roundbrackedclose_80", depth);
    return true;
}
bool yaoosl::parsing::instance::m_scope_81(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_scope(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_scope_81", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_scope_81", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_scope_81", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_scope(depth + 1);
    actual->if_body = val2;
    skip();
    trace("Returning true on m_scope_81", depth);
    return true;
}
bool yaoosl::parsing::instance::m_controlstructure_82(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_control_structure(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_controlstructure_82", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_controlstructure_82", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_controlstructure_82", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_control_structure(depth + 1);
    actual->if_body = val2;
    skip();
    trace("Returning true on m_controlstructure_82", depth);
    return true;
}
bool yaoosl::parsing::instance::m_statement_83(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_statement(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_statement_83", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_statement_83", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_statement_83", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_statement(depth + 1);
    actual->if_body = val2;
    skip();
    trace("Returning true on m_statement_83", depth);
    return true;
}
bool yaoosl::parsing::instance::alternatives84(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_scope_81(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives84", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_scope_81(false, actual, state, depth + 1);
            trace("Returning true on alternatives84", depth);
            return true;
        }
    }
    else if (m_controlstructure_82(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives84", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_controlstructure_82(false, actual, state, depth + 1);
            trace("Returning true on alternatives84", depth);
            return true;
        }
    }
    else if (m_statement_83(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives84", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_statement_83(false, actual, state, depth + 1);
            trace("Returning true on alternatives84", depth);
            return true;
        }
    }
    resetable1.reset();
    trace("Returning false on alternatives84", depth);
    return false;
}
bool yaoosl::parsing::instance::m_else_85(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__else(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_else_85", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_else_85", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_else_85", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__else(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    trace("Returning true on m_else_85", depth);
    return true;
}
bool yaoosl::parsing::instance::m_scope_86(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_scope(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_scope_86", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_scope_86", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_scope_86", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_scope(depth + 1);
    actual->else_body = val2;
    skip();
    trace("Returning true on m_scope_86", depth);
    return true;
}
bool yaoosl::parsing::instance::m_controlstructure_87(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_control_structure(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_controlstructure_87", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_controlstructure_87", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_controlstructure_87", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_control_structure(depth + 1);
    actual->else_body = val2;
    skip();
    trace("Returning true on m_controlstructure_87", depth);
    return true;
}
bool yaoosl::parsing::instance::m_statement_88(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_statement(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_statement_88", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_statement_88", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_statement_88", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_statement(depth + 1);
    actual->else_body = val2;
    skip();
    trace("Returning true on m_statement_88", depth);
    return true;
}
bool yaoosl::parsing::instance::alternatives89(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_scope_86(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives89", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_scope_86(false, actual, state, depth + 1);
            trace("Returning true on alternatives89", depth);
            return true;
        }
    }
    else if (m_controlstructure_87(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives89", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_controlstructure_87(false, actual, state, depth + 1);
            trace("Returning true on alternatives89", depth);
            return true;
        }
    }
    else if (m_statement_88(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives89", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_statement_88(false, actual, state, depth + 1);
            trace("Returning true on alternatives89", depth);
            return true;
        }
    }
    resetable1.reset();
    trace("Returning false on alternatives89", depth);
    return false;
}
bool yaoosl::parsing::instance::m_else_90(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__else(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_else_90", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_else_90", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_else_90", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__else(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    trace("Returning true on m_else_90", depth);
    return true;
}
bool yaoosl::parsing::instance::if91_92(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_else_90(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_else_85(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                trace("Returning false on XCG.Parsing.Statements.Match", depth);
                return false;
            }
            else
            {
                report("Failed to match { $ref: else ({ Token: else (else)}) }", depth);
                trace("Returning false on XCG.Parsing.Statements.Match", depth);
                return false;
            }
            alternatives89(true, actual, state, depth + 1);
            trace("Returning true on if91_92", depth);
            return true;
        }
        trace("Returning true on if91_92", depth);
        return true;
    }
    else
    {
        if (cond2)
        {
            if (m_else_85(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                trace("Returning false on XCG.Parsing.Statements.Match", depth);
                return false;
            }
            else
            {
                report("Failed to match { $ref: else ({ Token: else (else)}) }", depth);
                trace("Returning false on XCG.Parsing.Statements.Match", depth);
                return false;
            }
            alternatives89(false, actual, state, depth + 1);
            trace("Returning true on if91_92", depth);
            return true;
        }
        trace("Returning true on if91_92", depth);
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_if_else(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::if_else> fake;
    if_else_state state;
    if (!m_if_roundbrackedopen_expression_roundbrackedclose_80(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on if-else", depth);
        return false;
    }
    else if (!alternatives84(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on if-else", depth);
        return false;
    }
    else if (!if91_92(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on if-else", depth);
        return false;
    }
    trace("Returning true on if-else", depth);
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::if_else> yaoosl::parsing::instance::p_match_if_else(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::if_else>();
    std::shared_ptr<yaoosl::parsing::instance::if_else> fake;
    if_else_state state;
    resetable resetable2(*this);
    if (m_if_roundbrackedopen_expression_roundbrackedclose_80(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_if_roundbrackedopen_expression_roundbrackedclose_80(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (alternatives84(true, fake, state, depth + 1))
    {
        resetable3.reset();
        alternatives84(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (if91_92(true, fake, state, depth + 1))
    {
        resetable4.reset();
        if91_92(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_function_93(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_function(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_function_93", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_function_93", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_function_93", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_function(depth + 1);
    actual->content = val2;
    skip();
    trace("Returning true on m_function_93", depth);
    return true;
}
bool yaoosl::parsing::instance::m_whileloop_94(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_while_loop(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_whileloop_94", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_whileloop_94", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_whileloop_94", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_while_loop(depth + 1);
    actual->content = val2;
    skip();
    trace("Returning true on m_whileloop_94", depth);
    return true;
}
bool yaoosl::parsing::instance::m_ifelse_95(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_if_else(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_ifelse_95", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_ifelse_95", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_ifelse_95", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_if_else(depth + 1);
    actual->content = val2;
    skip();
    trace("Returning true on m_ifelse_95", depth);
    return true;
}
bool yaoosl::parsing::instance::m_scope_96(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_scope(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_scope_96", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_scope_96", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_scope_96", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_scope(depth + 1);
    actual->content = val2;
    skip();
    trace("Returning true on m_scope_96", depth);
    return true;
}
bool yaoosl::parsing::instance::alternatives97(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_function_93(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives97", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_function_93(false, actual, state, depth + 1);
            trace("Returning true on alternatives97", depth);
            return true;
        }
    }
    else if (m_whileloop_94(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives97", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_whileloop_94(false, actual, state, depth + 1);
            trace("Returning true on alternatives97", depth);
            return true;
        }
    }
    else if (m_ifelse_95(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives97", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_ifelse_95(false, actual, state, depth + 1);
            trace("Returning true on alternatives97", depth);
            return true;
        }
    }
    else if (m_scope_96(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives97", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_scope_96(false, actual, state, depth + 1);
            trace("Returning true on alternatives97", depth);
            return true;
        }
    }
    resetable1.reset();
    trace("Returning false on alternatives97", depth);
    return false;
}
bool yaoosl::parsing::instance::p_can_control_structure(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::control_structure> fake;
    control_structure_state state;
    if (!alternatives97(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on control-structure", depth);
        return false;
    }
    trace("Returning true on control-structure", depth);
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::control_structure> yaoosl::parsing::instance::p_match_control_structure(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::control_structure>();
    std::shared_ptr<yaoosl::parsing::instance::control_structure> fake;
    control_structure_state state;
    resetable resetable2(*this);
    if (alternatives97(true, fake, state, depth + 1))
    {
        resetable2.reset();
        alternatives97(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_controlstructure_98(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_control_structure(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_controlstructure_98", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_controlstructure_98", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_controlstructure_98", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_control_structure(depth + 1);
    actual->content.push_back(val2);
    skip();
    trace("Returning true on m_controlstructure_98", depth);
    return true;
}
bool yaoosl::parsing::instance::m_statement_99(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_statement(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_statement_99", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_statement_99", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_statement_99", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_statement(depth + 1);
    actual->content.push_back(val2);
    skip();
    trace("Returning true on m_statement_99", depth);
    return true;
}
bool yaoosl::parsing::instance::alternatives100(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_controlstructure_98(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives100", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_controlstructure_98(false, actual, state, depth + 1);
            trace("Returning true on alternatives100", depth);
            return true;
        }
    }
    else if (m_statement_99(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            trace("Returning true on alternatives100", depth);
            return true;
        }
        else
        {
            resetable1.reset();
            m_statement_99(false, actual, state, depth + 1);
            trace("Returning true on alternatives100", depth);
            return true;
        }
    }
    else if (!is_can)
    {
        report("Failed to match one of the following: { control-structure, statement }", depth);
    }
    resetable1.reset();
    trace("Returning false on alternatives100", depth);
    return false;
}
bool yaoosl::parsing::instance::while101_102(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = current() == '\0';
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives100(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = current() == '\0';
            resetable2.reset();
        }
        trace("Returning true on while101_102", depth);
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives100(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives100(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = current() == '\0';
            resetable2.reset();
        }
        trace("Returning true on while101_102", depth);
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_main(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::main> fake;
    main_state state;
    if (!while101_102(true, fake, state, depth + 1))
    {
        resetable1.reset();
        trace("Returning false on main", depth);
        return false;
    }
    trace("Returning true on main", depth);
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::main> yaoosl::parsing::instance::p_match_main(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::main>();
    std::shared_ptr<yaoosl::parsing::instance::main> fake;
    main_state state;
    resetable resetable2(*this);
    if (while101_102(true, fake, state, depth + 1))
    {
        resetable2.reset();
        while101_102(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_exparithmetic2_slash_expnullar_103(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token_slash(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_exparithmetic2_slash_expnullar_103", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_exparithmetic2_slash_expnullar_103", depth);
        return false;
    }
    if (p_can_exp_nullar(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_exparithmetic2_slash_expnullar_103", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_exparithmetic2_slash_expnullar_103", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_exparithmetic2_slash_expnullar_103", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token_slash(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_exp_nullar(depth + 1);
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op = '/';
    }
    trace("Returning true on m_exparithmetic2_slash_expnullar_103", depth);
    return true;
}
bool yaoosl::parsing::instance::m_exparithmetic2_star_expnullar_104(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token_star(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_exparithmetic2_star_expnullar_104", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_exparithmetic2_star_expnullar_104", depth);
        return false;
    }
    if (p_can_exp_nullar(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_exparithmetic2_star_expnullar_104", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_exparithmetic2_star_expnullar_104", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_exparithmetic2_star_expnullar_104", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token_star(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_exp_nullar(depth + 1);
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op = '*';
    }
    trace("Returning true on m_exparithmetic2_star_expnullar_104", depth);
    return true;
}
bool yaoosl::parsing::instance::m_expnullar_105(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_exp_nullar(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expnullar_105", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expnullar_105", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_expnullar_105", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_exp_nullar(depth + 1);
    actual->left = val2;
    skip();
    trace("Returning true on m_expnullar_105", depth);
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_arithmetic_2(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> fake;
    exp_arithmetic_2_state state;
    if (!m_expnullar_105(true, fake, state, depth + 1))
    {
        trace("Returning false on exp-arithmetic-2", depth);
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic2_slash_expnullar_103(true, fake, state, depth + 1))
        {
        }
        else if (m_exparithmetic2_star_expnullar_104(true, fake, state, depth + 1))
        {
        }
        else
        {
            trace("Returning true on exp-arithmetic-2", depth);
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> yaoosl::parsing::instance::lr_match_exp_arithmetic_2(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_2>();
    std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> fake;
    exp_arithmetic_2_state state;
    if (!m_expnullar_105(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning EmptyClosure on exp-arithmetic-2", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic2_slash_expnullar_103(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_2>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic2_slash_expnullar_103(false, actual, state, depth + 1);
        }
        else if (m_exparithmetic2_star_expnullar_104(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_2>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic2_star_expnullar_104(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_exparithmetic1_plus_exparithmetic2_106(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token_plus(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_exparithmetic1_plus_exparithmetic2_106", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_exparithmetic1_plus_exparithmetic2_106", depth);
        return false;
    }
    if (lr_can_exp_arithmetic_2(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_exparithmetic1_plus_exparithmetic2_106", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_exparithmetic1_plus_exparithmetic2_106", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_exparithmetic1_plus_exparithmetic2_106", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token_plus(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_arithmetic_2(depth + 1);
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op = '+';
    }
    trace("Returning true on m_exparithmetic1_plus_exparithmetic2_106", depth);
    return true;
}
bool yaoosl::parsing::instance::m_exparithmetic1_minus_exparithmetic2_107(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token_minus(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_exparithmetic1_minus_exparithmetic2_107", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_exparithmetic1_minus_exparithmetic2_107", depth);
        return false;
    }
    if (lr_can_exp_arithmetic_2(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_exparithmetic1_minus_exparithmetic2_107", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_exparithmetic1_minus_exparithmetic2_107", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_exparithmetic1_minus_exparithmetic2_107", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token_minus(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_arithmetic_2(depth + 1);
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op = '-';
    }
    trace("Returning true on m_exparithmetic1_minus_exparithmetic2_107", depth);
    return true;
}
bool yaoosl::parsing::instance::m_exparithmetic2_108(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_exp_arithmetic_2(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_exparithmetic2_108", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_exparithmetic2_108", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_exparithmetic2_108", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_exp_arithmetic_2(depth + 1);
    actual->left = val2;
    skip();
    trace("Returning true on m_exparithmetic2_108", depth);
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_arithmetic_1(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> fake;
    exp_arithmetic_1_state state;
    if (!m_exparithmetic2_108(true, fake, state, depth + 1))
    {
        trace("Returning false on exp-arithmetic-1", depth);
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic1_plus_exparithmetic2_106(true, fake, state, depth + 1))
        {
        }
        else if (m_exparithmetic1_minus_exparithmetic2_107(true, fake, state, depth + 1))
        {
        }
        else
        {
            trace("Returning true on exp-arithmetic-1", depth);
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> yaoosl::parsing::instance::lr_match_exp_arithmetic_1(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_1>();
    std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> fake;
    exp_arithmetic_1_state state;
    if (!m_exparithmetic2_108(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning EmptyClosure on exp-arithmetic-1", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic1_plus_exparithmetic2_106(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_1>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic1_plus_exparithmetic2_106(false, actual, state, depth + 1);
        }
        else if (m_exparithmetic1_minus_exparithmetic2_107(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_1>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic1_minus_exparithmetic2_107(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expcompare_lessthenequal_exparithmetic1_109(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__less_then_equal(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expcompare_lessthenequal_exparithmetic1_109", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expcompare_lessthenequal_exparithmetic1_109", depth);
        return false;
    }
    if (lr_can_exp_arithmetic_1(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expcompare_lessthenequal_exparithmetic1_109", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expcompare_lessthenequal_exparithmetic1_109", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_expcompare_lessthenequal_exparithmetic1_109", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__less_then_equal(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_arithmetic_1(depth + 1);
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op1 = '<';
    }
    if (!is_can)
    {
        actual->eq2 = '=';
    }
    trace("Returning true on m_expcompare_lessthenequal_exparithmetic1_109", depth);
    return true;
}
bool yaoosl::parsing::instance::m_expcompare_lessthen_exparithmetic1_110(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__less_then(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expcompare_lessthen_exparithmetic1_110", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expcompare_lessthen_exparithmetic1_110", depth);
        return false;
    }
    if (lr_can_exp_arithmetic_1(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expcompare_lessthen_exparithmetic1_110", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expcompare_lessthen_exparithmetic1_110", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_expcompare_lessthen_exparithmetic1_110", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__less_then(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_arithmetic_1(depth + 1);
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op1 = '<';
    }
    trace("Returning true on m_expcompare_lessthen_exparithmetic1_110", depth);
    return true;
}
bool yaoosl::parsing::instance::m_expcompare_greaterthenequal_exparithmetic1_111(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__greater_then_equal(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expcompare_greaterthenequal_exparithmetic1_111", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expcompare_greaterthenequal_exparithmetic1_111", depth);
        return false;
    }
    if (lr_can_exp_arithmetic_1(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expcompare_greaterthenequal_exparithmetic1_111", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expcompare_greaterthenequal_exparithmetic1_111", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_expcompare_greaterthenequal_exparithmetic1_111", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__greater_then_equal(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_arithmetic_1(depth + 1);
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op1 = '>';
    }
    if (!is_can)
    {
        actual->op2 = '=';
    }
    trace("Returning true on m_expcompare_greaterthenequal_exparithmetic1_111", depth);
    return true;
}
bool yaoosl::parsing::instance::m_expcompare_greaterthen_exparithmetic1_112(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__greater_then(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expcompare_greaterthen_exparithmetic1_112", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expcompare_greaterthen_exparithmetic1_112", depth);
        return false;
    }
    if (lr_can_exp_arithmetic_1(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expcompare_greaterthen_exparithmetic1_112", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expcompare_greaterthen_exparithmetic1_112", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_expcompare_greaterthen_exparithmetic1_112", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__greater_then(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_arithmetic_1(depth + 1);
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op1 = '>';
    }
    trace("Returning true on m_expcompare_greaterthen_exparithmetic1_112", depth);
    return true;
}
bool yaoosl::parsing::instance::m_exparithmetic1_113(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_exp_arithmetic_1(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_exparithmetic1_113", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_exparithmetic1_113", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_exparithmetic1_113", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_exp_arithmetic_1(depth + 1);
    actual->left = val2;
    skip();
    trace("Returning true on m_exparithmetic1_113", depth);
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_compare(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_compare> fake;
    exp_compare_state state;
    if (!m_exparithmetic1_113(true, fake, state, depth + 1))
    {
        trace("Returning false on exp-compare", depth);
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expcompare_lessthenequal_exparithmetic1_109(true, fake, state, depth + 1))
        {
        }
        else if (m_expcompare_lessthen_exparithmetic1_110(true, fake, state, depth + 1))
        {
        }
        else if (m_expcompare_greaterthenequal_exparithmetic1_111(true, fake, state, depth + 1))
        {
        }
        else if (m_expcompare_greaterthen_exparithmetic1_112(true, fake, state, depth + 1))
        {
        }
        else
        {
            trace("Returning true on exp-compare", depth);
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_compare> yaoosl::parsing::instance::lr_match_exp_compare(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
    std::shared_ptr<yaoosl::parsing::instance::exp_compare> fake;
    exp_compare_state state;
    if (!m_exparithmetic1_113(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning EmptyClosure on exp-compare", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expcompare_lessthenequal_exparithmetic1_109(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_lessthenequal_exparithmetic1_109(false, actual, state, depth + 1);
        }
        else if (m_expcompare_lessthen_exparithmetic1_110(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_lessthen_exparithmetic1_110(false, actual, state, depth + 1);
        }
        else if (m_expcompare_greaterthenequal_exparithmetic1_111(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_greaterthenequal_exparithmetic1_111(false, actual, state, depth + 1);
        }
        else if (m_expcompare_greaterthen_exparithmetic1_112(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_greaterthen_exparithmetic1_112(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expequality_lessthenequal_expcompare_114(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__less_then_equal(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expequality_lessthenequal_expcompare_114", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expequality_lessthenequal_expcompare_114", depth);
        return false;
    }
    if (lr_can_exp_compare(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expequality_lessthenequal_expcompare_114", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expequality_lessthenequal_expcompare_114", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_expequality_lessthenequal_expcompare_114", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__less_then_equal(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_compare(depth + 1);
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op1 = '<';
    }
    if (!is_can)
    {
        actual->eq2 = '=';
    }
    trace("Returning true on m_expequality_lessthenequal_expcompare_114", depth);
    return true;
}
bool yaoosl::parsing::instance::m_expequality_lessthen_expcompare_115(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__less_then(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expequality_lessthen_expcompare_115", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expequality_lessthen_expcompare_115", depth);
        return false;
    }
    if (lr_can_exp_compare(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expequality_lessthen_expcompare_115", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expequality_lessthen_expcompare_115", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_expequality_lessthen_expcompare_115", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__less_then(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_compare(depth + 1);
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op1 = '<';
    }
    trace("Returning true on m_expequality_lessthen_expcompare_115", depth);
    return true;
}
bool yaoosl::parsing::instance::m_expequality_greaterthenequal_expcompare_116(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__greater_then_equal(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expequality_greaterthenequal_expcompare_116", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expequality_greaterthenequal_expcompare_116", depth);
        return false;
    }
    if (lr_can_exp_compare(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expequality_greaterthenequal_expcompare_116", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expequality_greaterthenequal_expcompare_116", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_expequality_greaterthenequal_expcompare_116", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__greater_then_equal(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_compare(depth + 1);
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op1 = '>';
    }
    if (!is_can)
    {
        actual->op2 = '=';
    }
    trace("Returning true on m_expequality_greaterthenequal_expcompare_116", depth);
    return true;
}
bool yaoosl::parsing::instance::m_expequality_greaterthen_expcompare_117(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__greater_then(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expequality_greaterthen_expcompare_117", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expequality_greaterthen_expcompare_117", depth);
        return false;
    }
    if (lr_can_exp_compare(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expequality_greaterthen_expcompare_117", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expequality_greaterthen_expcompare_117", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_expequality_greaterthen_expcompare_117", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__greater_then(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_compare(depth + 1);
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op1 = '>';
    }
    trace("Returning true on m_expequality_greaterthen_expcompare_117", depth);
    return true;
}
bool yaoosl::parsing::instance::m_expcompare_118(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_exp_compare(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expcompare_118", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expcompare_118", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_expcompare_118", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_exp_compare(depth + 1);
    actual->left = val2;
    skip();
    trace("Returning true on m_expcompare_118", depth);
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_equality(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_equality> fake;
    exp_equality_state state;
    if (!m_expcompare_118(true, fake, state, depth + 1))
    {
        trace("Returning false on exp-equality", depth);
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expequality_lessthenequal_expcompare_114(true, fake, state, depth + 1))
        {
        }
        else if (m_expequality_lessthen_expcompare_115(true, fake, state, depth + 1))
        {
        }
        else if (m_expequality_greaterthenequal_expcompare_116(true, fake, state, depth + 1))
        {
        }
        else if (m_expequality_greaterthen_expcompare_117(true, fake, state, depth + 1))
        {
        }
        else
        {
            trace("Returning true on exp-equality", depth);
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_equality> yaoosl::parsing::instance::lr_match_exp_equality(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
    std::shared_ptr<yaoosl::parsing::instance::exp_equality> fake;
    exp_equality_state state;
    if (!m_expcompare_118(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning EmptyClosure on exp-equality", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expequality_lessthenequal_expcompare_114(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_lessthenequal_expcompare_114(false, actual, state, depth + 1);
        }
        else if (m_expequality_lessthen_expcompare_115(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_lessthen_expcompare_115(false, actual, state, depth + 1);
        }
        else if (m_expequality_greaterthenequal_expcompare_116(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_greaterthenequal_expcompare_116(false, actual, state, depth + 1);
        }
        else if (m_expequality_greaterthen_expcompare_117(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_greaterthen_expcompare_117(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expand_and_expequality_119(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and>& actual, yaoosl::parsing::instance::exp_and_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__and(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expand_and_expequality_119", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expand_and_expequality_119", depth);
        return false;
    }
    if (lr_can_exp_equality(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expand_and_expequality_119", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expand_and_expequality_119", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_expand_and_expequality_119", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__and(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_equality(depth + 1);
    actual->right = val6;
    skip();
    trace("Returning true on m_expand_and_expequality_119", depth);
    return true;
}
bool yaoosl::parsing::instance::m_expequality_120(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and>& actual, yaoosl::parsing::instance::exp_and_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_exp_equality(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expequality_120", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expequality_120", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_expequality_120", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_exp_equality(depth + 1);
    actual->left = val2;
    skip();
    trace("Returning true on m_expequality_120", depth);
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_and(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_and> fake;
    exp_and_state state;
    if (!m_expequality_120(true, fake, state, depth + 1))
    {
        trace("Returning false on exp-and", depth);
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expand_and_expequality_119(true, fake, state, depth + 1))
        {
        }
        else
        {
            trace("Returning true on exp-and", depth);
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_and> yaoosl::parsing::instance::lr_match_exp_and(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_and>();
    std::shared_ptr<yaoosl::parsing::instance::exp_and> fake;
    exp_and_state state;
    if (!m_expequality_120(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning EmptyClosure on exp-and", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expand_and_expequality_119(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_and>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expand_and_expequality_119(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expor_or_expequality_121(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or>& actual, yaoosl::parsing::instance::exp_or_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__or(depth + 1);
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expor_or_expequality_121", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expor_or_expequality_121", depth);
        return false;
    }
    if (lr_can_exp_equality(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expor_or_expequality_121", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expor_or_expequality_121", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_expor_or_expequality_121", depth);
        return true;
    }
    resetable1.reset();
    auto l5 = token__or(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_equality(depth + 1);
    actual->right = val6;
    skip();
    trace("Returning true on m_expor_or_expequality_121", depth);
    return true;
}
bool yaoosl::parsing::instance::m_expequality_122(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or>& actual, yaoosl::parsing::instance::exp_or_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_exp_equality(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        trace("Returning false on m_expequality_122", depth);
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning false on m_expequality_122", depth);
        return false;
    }
    if (is_can)
    {
        trace("Returning true on m_expequality_122", depth);
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_exp_equality(depth + 1);
    actual->left = val2;
    skip();
    trace("Returning true on m_expequality_122", depth);
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_or(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_or> fake;
    exp_or_state state;
    if (!m_expequality_122(true, fake, state, depth + 1))
    {
        trace("Returning false on exp-or", depth);
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expor_or_expequality_121(true, fake, state, depth + 1))
        {
        }
        else
        {
            trace("Returning true on exp-or", depth);
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_or> yaoosl::parsing::instance::lr_match_exp_or(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_or>();
    std::shared_ptr<yaoosl::parsing::instance::exp_or> fake;
    exp_or_state state;
    if (!m_expequality_122(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        trace("Returning EmptyClosure on exp-or", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expor_or_expequality_121(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_or>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expor_or_expequality_121(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
void yaoosl::parsing::instance::report(std::string_view message, size_t depth)
{
    std::cout << "[L" << m_line << "]" << "[C" << m_column << "] " << message << "\n";
}
void yaoosl::parsing::instance::trace(std::string_view message, size_t depth)
{
    std::cout << std::string(depth, ' ') << "[L" << m_line << "]" << "[C" << m_column << "] " << message << "\n";
}
yaoosl::parsing::instance::token yaoosl::parsing::instance::create_token(size_t length, tok type)
{
    token t;
    t.file = m_file;
    t.line = m_line;
    t.column = m_column;
    t.offset = m_offset;
    t.length = length;
    t.type = type;
    for (auto i = 0; i < length; i++)
    {
        next();
    }
    return t;
}
std::shared_ptr<yaoosl::parsing::instance::main> yaoosl::parsing::instance::parse()
{
    return p_match_main(0);
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<call> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("call:");
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->method.line) + "; C" + std::to_string(node->method.column) + "; O" + std::to_string(node->method.offset) + ") `" + std::string(contents.substr(node->method.offset, node->method.length).begin(), contents.substr(node->method.offset, node->method.length).end()) + "`");
    for (auto element : node->args)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [args]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_nullar> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_nullar:");
    switch (node->value.index())
    {
        case 0:
        if (std::get<std::shared_ptr<call>>(node->value))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<call>>(node->value), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [value]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<statement>>(node->value))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<statement>>(node->value), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [value]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 2:
        output.push_back(std::string("  ") + "token (L" + std::to_string(std::get<token>(node->value).line) + "; C" + std::to_string(std::get<token>(node->value).column) + "; O" + std::to_string(std::get<token>(node->value).offset) + ") `" + std::string(contents.substr(std::get<token>(node->value).offset, std::get<token>(node->value).length).begin(), contents.substr(std::get<token>(node->value).offset, std::get<token>(node->value).length).end()) + "`");
        break;
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_assignment> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_assignment:");
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->name.line) + "; C" + std::to_string(node->name.column) + "; O" + std::to_string(node->name.offset) + ") `" + std::string(contents.substr(node->name.offset, node->name.length).begin(), contents.substr(node->name.offset, node->name.length).end()) + "`");
    if (node->value)
    {
        auto lines = create_string_tree(node->value, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [value]" "\u001b[0m" : line));
            first = false;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<return_statement> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("return_statement:");
    if (node->expression)
    {
        auto lines = create_string_tree(node->expression, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [expression]" "\u001b[0m" : line));
            first = false;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<expression> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("expression:");
    switch (node->expression.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_assignment>>(node->expression))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_assignment>>(node->expression), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [expression]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_or>>(node->expression))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_or>>(node->expression), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [expression]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<statement> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("statement:");
    switch (node->expression.index())
    {
        case 0:
        if (std::get<std::shared_ptr<return_statement>>(node->expression))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<return_statement>>(node->expression), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [expression]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<expression>>(node->expression))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<expression>>(node->expression), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [expression]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<function_arg> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("function_arg:");
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->name.line) + "; C" + std::to_string(node->name.column) + "; O" + std::to_string(node->name.offset) + ") `" + std::string(contents.substr(node->name.offset, node->name.length).begin(), contents.substr(node->name.offset, node->name.length).end()) + "`");
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<scope> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("scope:");
    for (auto element : node->body)
    {
        switch (element.index())
        {
            case 0:
            if (std::get<std::shared_ptr<control_structure>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<control_structure>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [body]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
            case 1:
            if (std::get<std::shared_ptr<statement>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<statement>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [body]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<function> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("function:");
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->name.line) + "; C" + std::to_string(node->name.column) + "; O" + std::to_string(node->name.offset) + ") `" + std::string(contents.substr(node->name.offset, node->name.length).begin(), contents.substr(node->name.offset, node->name.length).end()) + "`");
    for (auto element : node->args)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [args]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    if (node->body)
    {
        auto lines = create_string_tree(node->body, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [body]" "\u001b[0m" : line));
            first = false;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<while_loop> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("while_loop:");
    if (node->condition)
    {
        auto lines = create_string_tree(node->condition, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [condition]" "\u001b[0m" : line));
            first = false;
        }
    }
    switch (node->body.index())
    {
        case 0:
        if (std::get<std::shared_ptr<scope>>(node->body))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<scope>>(node->body), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [body]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<control_structure>>(node->body))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<control_structure>>(node->body), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [body]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 2:
        if (std::get<std::shared_ptr<statement>>(node->body))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<statement>>(node->body), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [body]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<if_else> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("if_else:");
    if (node->condition)
    {
        auto lines = create_string_tree(node->condition, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [condition]" "\u001b[0m" : line));
            first = false;
        }
    }
    switch (node->if_body.index())
    {
        case 0:
        if (std::get<std::shared_ptr<scope>>(node->if_body))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<scope>>(node->if_body), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [if_body]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<control_structure>>(node->if_body))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<control_structure>>(node->if_body), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [if_body]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 2:
        if (std::get<std::shared_ptr<statement>>(node->if_body))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<statement>>(node->if_body), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [if_body]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    switch (node->else_body.index())
    {
        case 0:
        if (std::get<std::shared_ptr<scope>>(node->else_body))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<scope>>(node->else_body), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [else_body]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<control_structure>>(node->else_body))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<control_structure>>(node->else_body), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [else_body]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 2:
        if (std::get<std::shared_ptr<statement>>(node->else_body))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<statement>>(node->else_body), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [else_body]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<control_structure> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("control_structure:");
    switch (node->content.index())
    {
        case 0:
        if (std::get<std::shared_ptr<function>>(node->content))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<function>>(node->content), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [content]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<while_loop>>(node->content))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<while_loop>>(node->content), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [content]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 2:
        if (std::get<std::shared_ptr<if_else>>(node->content))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<if_else>>(node->content), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [content]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 3:
        if (std::get<std::shared_ptr<scope>>(node->content))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<scope>>(node->content), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [content]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<main> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("main:");
    for (auto element : node->content)
    {
        switch (element.index())
        {
            case 0:
            if (std::get<std::shared_ptr<control_structure>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<control_structure>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [content]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
            case 1:
            if (std::get<std::shared_ptr<statement>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<statement>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [content]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_arithmetic_2> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_arithmetic_2:");
    if (node->op.has_value())
    {
        output.push_back(std::string("  ") + "`" + node->op.value() + "`");
    }
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_arithmetic_2>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_arithmetic_2>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_nullar>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_nullar>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    if (node->right)
    {
        auto lines = create_string_tree(node->right, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [right]" "\u001b[0m" : line));
            first = false;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_arithmetic_1> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_arithmetic_1:");
    if (node->op.has_value())
    {
        output.push_back(std::string("  ") + "`" + node->op.value() + "`");
    }
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_arithmetic_1>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_arithmetic_1>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_arithmetic_2>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_arithmetic_2>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    if (node->right)
    {
        auto lines = create_string_tree(node->right, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [right]" "\u001b[0m" : line));
            first = false;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_compare> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_compare:");
    if (node->op1.has_value())
    {
        output.push_back(std::string("  ") + "`" + node->op1.value() + "`");
    }
    if (node->eq2.has_value())
    {
        output.push_back(std::string("  ") + "`" + node->eq2.value() + "`");
    }
    if (node->op2.has_value())
    {
        output.push_back(std::string("  ") + "`" + node->op2.value() + "`");
    }
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_compare>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_compare>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_arithmetic_1>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_arithmetic_1>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    if (node->right)
    {
        auto lines = create_string_tree(node->right, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [right]" "\u001b[0m" : line));
            first = false;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_equality> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_equality:");
    if (node->op1.has_value())
    {
        output.push_back(std::string("  ") + "`" + node->op1.value() + "`");
    }
    if (node->eq2.has_value())
    {
        output.push_back(std::string("  ") + "`" + node->eq2.value() + "`");
    }
    if (node->op2.has_value())
    {
        output.push_back(std::string("  ") + "`" + node->op2.value() + "`");
    }
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_equality>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_equality>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_compare>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_compare>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    if (node->right)
    {
        auto lines = create_string_tree(node->right, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [right]" "\u001b[0m" : line));
            first = false;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_and> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_and:");
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_and>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_and>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_equality>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_equality>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    if (node->right)
    {
        auto lines = create_string_tree(node->right, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [right]" "\u001b[0m" : line));
            first = false;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_or> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_or:");
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_or>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_or>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_equality>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_equality>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    if (node->right)
    {
        auto lines = create_string_tree(node->right, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [right]" "\u001b[0m" : line));
            first = false;
        }
    }
    return output;
}
