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
        return {};
    }
    auto resultVariable1 = m_offset - resetable1.m_offset;
    resetable1.reset();
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
        return {};
    }
    auto resultVariable2 = m_offset - resetable1.m_offset;
    resetable1.reset();
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
        return {};
    }
    auto resultVariable3 = m_offset - resetable1.m_offset;
    resetable1.reset();
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
        return {};
    }
    auto resultVariable4 = m_offset - resetable1.m_offset;
    resetable1.reset();
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
        return {};
    }
    auto resultVariable5 = m_offset - resetable1.m_offset;
    resetable1.reset();
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
        return {};
    }
    auto resultVariable6 = m_offset - resetable1.m_offset;
    resetable1.reset();
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
        return {};
    }
    auto resultVariable7 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable7;
}
std::optional<size_t> yaoosl::parsing::instance::token_true(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "true";
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
        return {};
    }
    auto resultVariable8 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable8;
}
std::optional<size_t> yaoosl::parsing::instance::token_false(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "false";
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
        return {};
    }
    auto resultVariable9 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable9;
}
std::optional<size_t> yaoosl::parsing::instance::token_boolean(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        std::optional<size_t> res3 = token_true(depth + 1);
        if (res3.has_value())
        {
            count2++;
            for (size_t i = 0; i < res3; i++)
            {
                next();
            }
            continue;
        }
        std::optional<size_t> res4 = token_false(depth + 1);
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
        return {};
    }
    auto resultVariable10 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable10;
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
        return {};
    }
    auto resultVariable11 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable11;
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
        return {};
    }
    auto resultVariable12 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable12;
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
        return {};
    }
    auto resultVariable13 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable13;
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
        return {};
    }
    auto resultVariable14 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable14;
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
        return {};
    }
    auto resultVariable15 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable15;
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
        return {};
    }
    auto resultVariable16 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable16;
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
        return {};
    }
    auto resultVariable17 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable17;
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
        return {};
    }
    auto resultVariable18 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable18;
}
std::optional<size_t> yaoosl::parsing::instance::token__square_bracked_open(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == '[')
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
        return {};
    }
    auto resultVariable19 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable19;
}
std::optional<size_t> yaoosl::parsing::instance::token__square_bracked_close(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == ']')
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
        return {};
    }
    auto resultVariable20 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable20;
}
std::optional<size_t> yaoosl::parsing::instance::token__dot(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == '.')
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
        return {};
    }
    auto resultVariable21 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable21;
}
std::optional<size_t> yaoosl::parsing::instance::token__typeof(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "typeof";
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
        return {};
    }
    auto resultVariable22 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable22;
}
std::optional<size_t> yaoosl::parsing::instance::token__nameof(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "nameof";
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
        return {};
    }
    auto resultVariable23 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable23;
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
        return {};
    }
    auto resultVariable24 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable24;
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
        return {};
    }
    auto resultVariable25 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable25;
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
        return {};
    }
    auto resultVariable26 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable26;
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
        return {};
    }
    auto resultVariable27 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable27;
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
        return {};
    }
    auto resultVariable28 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable28;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_137(size_t depth)
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
        return {};
    }
    auto resultVariable29 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable29;
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
        return {};
    }
    auto resultVariable30 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable30;
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
        return {};
    }
    auto resultVariable31 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable31;
}
std::optional<size_t> yaoosl::parsing::instance::token__get(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "get";
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
        return {};
    }
    auto resultVariable32 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable32;
}
std::optional<size_t> yaoosl::parsing::instance::token__set(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "set";
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
        return {};
    }
    auto resultVariable33 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable33;
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
        return {};
    }
    auto resultVariable34 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable34;
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
        return {};
    }
    auto resultVariable35 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable35;
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
        return {};
    }
    auto resultVariable36 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable36;
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
        return {};
    }
    auto resultVariable37 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable37;
}
std::optional<size_t> yaoosl::parsing::instance::token__case(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "case";
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
        return {};
    }
    auto resultVariable38 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable38;
}
std::optional<size_t> yaoosl::parsing::instance::token__colon(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == ':')
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
        return {};
    }
    auto resultVariable39 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable39;
}
std::optional<size_t> yaoosl::parsing::instance::token__switch(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "switch";
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
        return {};
    }
    auto resultVariable40 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable40;
}
std::optional<size_t> yaoosl::parsing::instance::token__default(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "default";
        if (m_contents.length() - m_offset >= 7 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 7, str3, str3 + 7))
        {
            count2++;
            for (size_t i = 0; i < 7; i++)
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
        return {};
    }
    auto resultVariable41 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable41;
}
std::optional<size_t> yaoosl::parsing::instance::token__public(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "public";
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
        return {};
    }
    auto resultVariable42 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable42;
}
std::optional<size_t> yaoosl::parsing::instance::token__local(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "local";
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
        return {};
    }
    auto resultVariable43 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable43;
}
std::optional<size_t> yaoosl::parsing::instance::token__derived(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "derived";
        if (m_contents.length() - m_offset >= 7 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 7, str3, str3 + 7))
        {
            count2++;
            for (size_t i = 0; i < 7; i++)
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
        return {};
    }
    auto resultVariable44 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable44;
}
std::optional<size_t> yaoosl::parsing::instance::token__private(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "private";
        if (m_contents.length() - m_offset >= 7 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 7, str3, str3 + 7))
        {
            count2++;
            for (size_t i = 0; i < 7; i++)
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
        return {};
    }
    auto resultVariable45 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable45;
}
std::optional<size_t> yaoosl::parsing::instance::token__namespace(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "namespace";
        if (m_contents.length() - m_offset >= 9 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 9, str3, str3 + 9))
        {
            count2++;
            for (size_t i = 0; i < 9; i++)
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
        return {};
    }
    auto resultVariable46 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable46;
}
std::optional<size_t> yaoosl::parsing::instance::token__class(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "class";
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
        return {};
    }
    auto resultVariable47 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable47;
}
std::optional<size_t> yaoosl::parsing::instance::token__unbound(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "unbound";
        if (m_contents.length() - m_offset >= 7 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 7, str3, str3 + 7))
        {
            count2++;
            for (size_t i = 0; i < 7; i++)
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
        return {};
    }
    auto resultVariable48 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable48;
}
std::optional<size_t> yaoosl::parsing::instance::token__tilde(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == '~')
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
        return {};
    }
    auto resultVariable49 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable49;
}
std::optional<size_t> yaoosl::parsing::instance::token__delete(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "delete";
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
        return {};
    }
    auto resultVariable50 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable50;
}
std::optional<size_t> yaoosl::parsing::instance::token__conversion(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "conversion";
        if (m_contents.length() - m_offset >= 10 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 10, str3, str3 + 10))
        {
            count2++;
            for (size_t i = 0; i < 10; i++)
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
        return {};
    }
    auto resultVariable51 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable51;
}
bool yaoosl::parsing::instance::m_ident_roundbrackedopen_52(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    return true;
}
bool yaoosl::parsing::instance::m_expression_53(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_expression(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    lr_match_expression(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expression_54(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_expression(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_expression(depth + 1);
    actual->args.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_roundbrackedclose_55(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_comma_expression_56(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_expression(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_expression(depth + 1);
    actual->args.push_back(val6);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_comma_57(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives58(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_comma_expression_56(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_comma_expression_56(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_comma_57(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_comma_57(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (!is_can)
    {
        report("Failed to match one of the following: { ,, expression, , }", depth);
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_roundbrackedclose_55(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::while59_60(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_roundbrackedclose_55(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives58(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_55(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives58(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives58(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_55(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_expression_53(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_expression(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    lr_match_expression(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::if61_62(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_expression_53(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_expression_54(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: expression (XCG.Parsing.LeftRecursive) }", depth);
                return false;
            }
            while59_60(true, actual, state, depth + 1);
            return true;
        }
        return true;
    }
    else
    {
        if (cond2)
        {
            if (m_expression_54(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: expression (XCG.Parsing.LeftRecursive) }", depth);
                return false;
            }
            while59_60(false, actual, state, depth + 1);
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_roundbrackedclose_63(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_call(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::call> fake;
    call_state state;
    if (!m_ident_roundbrackedopen_52(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!if61_62(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_roundbrackedclose_63(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::call> yaoosl::parsing::instance::p_match_call(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::call>();
    std::shared_ptr<yaoosl::parsing::instance::call> fake;
    call_state state;
    resetable resetable2(*this);
    if (m_ident_roundbrackedopen_52(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_ident_roundbrackedopen_52(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (if61_62(true, fake, state, depth + 1))
    {
        resetable3.reset();
        if61_62(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (m_roundbrackedclose_63(true, fake, state, depth + 1))
    {
        resetable4.reset();
        m_roundbrackedclose_63(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_ident_64(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage_item>& actual, yaoosl::parsing::instance::template_usage_item_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->key = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_template_usage_item(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::template_usage_item> fake;
    template_usage_item_state state;
    if (!m_ident_64(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::template_usage_item> yaoosl::parsing::instance::p_match_template_usage_item(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::template_usage_item>();
    std::shared_ptr<yaoosl::parsing::instance::template_usage_item> fake;
    template_usage_item_state state;
    resetable resetable2(*this);
    if (m_ident_64(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_ident_64(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_lessthen_65(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__less_then(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_templateusageitem_66(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_template_usage_item(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_template_usage_item(depth + 1);
    actual->items.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_comma_67(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_comma_templateusageitem_68(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_template_usage_item(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_template_usage_item(depth + 1);
    actual->items.push_back(val6);
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives69(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_comma_templateusageitem_68(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_comma_templateusageitem_68(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (!is_can)
    {
        report("Failed to match one of the following: { ,, template-usage-item }", depth);
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_comma_67(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::while70_71(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_comma_67(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (cond3 && current() != '\0')
        {
            while (!alternatives69(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_comma_67(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (cond3 && current() != '\0')
        {
            if (!alternatives69(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives69(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_comma_67(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_greaterthen_72(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__greater_then(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_template_usage(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::template_usage> fake;
    template_usage_state state;
    if (!m_lessthen_65(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_templateusageitem_66(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!while70_71(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_greaterthen_72(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::template_usage> yaoosl::parsing::instance::p_match_template_usage(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::template_usage>();
    std::shared_ptr<yaoosl::parsing::instance::template_usage> fake;
    template_usage_state state;
    resetable resetable2(*this);
    if (m_lessthen_65(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_lessthen_65(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (m_templateusageitem_66(true, fake, state, depth + 1))
    {
        resetable3.reset();
        m_templateusageitem_66(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (while70_71(true, fake, state, depth + 1))
    {
        resetable4.reset();
        while70_71(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable5(*this);
    if (m_greaterthen_72(true, fake, state, depth + 1))
    {
        resetable5.reset();
        m_greaterthen_72(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_ident_73(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition_item>& actual, yaoosl::parsing::instance::template_definition_item_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->key = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_equal_74(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition_item>& actual, yaoosl::parsing::instance::template_definition_item_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__equal(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__equal(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_equal_expvalue_75(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition_item>& actual, yaoosl::parsing::instance::template_definition_item_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__equal(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_exp_value(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__equal(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_exp_value(depth + 1);
    actual->value = val6;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_equal_74(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition_item>& actual, yaoosl::parsing::instance::template_definition_item_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__equal(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__equal(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::if76_77(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition_item>& actual, yaoosl::parsing::instance::template_definition_item_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_equal_74(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_equal_expvalue_75(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: = ({ Token: = (=)}), $ref: exp-value (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
    else
    {
        if (cond2)
        {
            if (m_equal_expvalue_75(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: = ({ Token: = (=)}), $ref: exp-value (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_template_definition_item(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::template_definition_item> fake;
    template_definition_item_state state;
    if (!m_ident_73(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!if76_77(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::template_definition_item> yaoosl::parsing::instance::p_match_template_definition_item(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::template_definition_item>();
    std::shared_ptr<yaoosl::parsing::instance::template_definition_item> fake;
    template_definition_item_state state;
    resetable resetable2(*this);
    if (m_ident_73(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_ident_73(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (if76_77(true, fake, state, depth + 1))
    {
        resetable3.reset();
        if76_77(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_lessthen_78(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__less_then(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_templatedefinitionitem_79(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_template_definition_item(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_template_definition_item(depth + 1);
    actual->items.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_comma_80(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_comma_templatedefinitionitem_81(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_template_definition_item(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_template_definition_item(depth + 1);
    actual->items.push_back(val6);
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives82(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_comma_templatedefinitionitem_81(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_comma_templatedefinitionitem_81(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (!is_can)
    {
        report("Failed to match one of the following: { ,, template-definition-item }", depth);
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_comma_80(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::while83_84(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_comma_80(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (cond3 && current() != '\0')
        {
            while (!alternatives82(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_comma_80(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (cond3 && current() != '\0')
        {
            if (!alternatives82(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives82(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_comma_80(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_greaterthen_85(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__greater_then(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_template_definition(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::template_definition> fake;
    template_definition_state state;
    if (!m_lessthen_78(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_templatedefinitionitem_79(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!while83_84(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_greaterthen_85(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::template_definition> yaoosl::parsing::instance::p_match_template_definition(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::template_definition>();
    std::shared_ptr<yaoosl::parsing::instance::template_definition> fake;
    template_definition_state state;
    resetable resetable2(*this);
    if (m_lessthen_78(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_lessthen_78(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (m_templatedefinitionitem_79(true, fake, state, depth + 1))
    {
        resetable3.reset();
        m_templatedefinitionitem_79(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (while83_84(true, fake, state, depth + 1))
    {
        resetable4.reset();
        while83_84(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable5(*this);
    if (m_greaterthen_85(true, fake, state, depth + 1))
    {
        resetable5.reset();
        m_greaterthen_85(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_ident_86(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_start>& actual, yaoosl::parsing::instance::exp_chain_start_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->part = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_call_87(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_start>& actual, yaoosl::parsing::instance::exp_chain_start_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_call(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_call(depth + 1);
    actual->part = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_exp_chain_start(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_chain_start> fake;
    exp_chain_start_state state;
    if (!m_ident_86(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_call_87(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::exp_chain_start> yaoosl::parsing::instance::p_match_exp_chain_start(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_chain_start>();
    std::shared_ptr<yaoosl::parsing::instance::exp_chain_start> fake;
    exp_chain_start_state state;
    resetable resetable2(*this);
    if (m_ident_86(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_ident_86(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (m_call_87(true, fake, state, depth + 1))
    {
        resetable3.reset();
        m_call_87(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_squarebrackedopen_88(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_indexer>& actual, yaoosl::parsing::instance::exp_chain_indexer_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__square_bracked_open(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__square_bracked_open(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_squarebrackedclose_89(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_indexer>& actual, yaoosl::parsing::instance::exp_chain_indexer_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__square_bracked_close(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__square_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_exp_chain_indexer(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_chain_indexer> fake;
    exp_chain_indexer_state state;
    if (!m_squarebrackedopen_88(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_squarebrackedclose_89(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::exp_chain_indexer> yaoosl::parsing::instance::p_match_exp_chain_indexer(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_chain_indexer>();
    std::shared_ptr<yaoosl::parsing::instance::exp_chain_indexer> fake;
    exp_chain_indexer_state state;
    resetable resetable2(*this);
    if (m_squarebrackedopen_88(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_squarebrackedopen_88(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (m_squarebrackedclose_89(true, fake, state, depth + 1))
    {
        resetable3.reset();
        m_squarebrackedclose_89(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_dot_ident_90(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_access>& actual, yaoosl::parsing::instance::exp_chain_access_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__dot(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l7 = token__dot(depth + 1).value();
    for (;l7 != 0; l7--)
    {
        next();
    }
    skip();
    auto val8 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->capture40 = val8;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_exp_chain_access(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_chain_access> fake;
    exp_chain_access_state state;
    if (!m_dot_ident_90(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::exp_chain_access> yaoosl::parsing::instance::p_match_exp_chain_access(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_chain_access>();
    std::shared_ptr<yaoosl::parsing::instance::exp_chain_access> fake;
    exp_chain_access_state state;
    resetable resetable2(*this);
    if (m_dot_ident_90(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_dot_ident_90(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_dot_call_91(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_call>& actual, yaoosl::parsing::instance::exp_chain_call_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__dot(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_call(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__dot(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_call(depth + 1);
    actual->capture42 = val6;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_exp_chain_call(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_chain_call> fake;
    exp_chain_call_state state;
    if (!m_dot_call_91(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::exp_chain_call> yaoosl::parsing::instance::p_match_exp_chain_call(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_chain_call>();
    std::shared_ptr<yaoosl::parsing::instance::exp_chain_call> fake;
    exp_chain_call_state state;
    resetable resetable2(*this);
    if (m_dot_call_91(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_dot_call_91(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_typeof_roundbrackedopen_typenavigation_roundbrackedclose_92(bool is_can, std::shared_ptr<yaoosl::parsing::instance::typeof>& actual, yaoosl::parsing::instance::typeof_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__typeof(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_type_navigation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l9 = token__typeof(depth + 1).value();
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
    auto val12 = lr_match_type_navigation(depth + 1);
    actual->value = val12;
    skip();
    auto l14 = token__round_bracked_close(depth + 1).value();
    for (;l14 != 0; l14--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_typeof(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::typeof> fake;
    typeof_state state;
    if (!m_typeof_roundbrackedopen_typenavigation_roundbrackedclose_92(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::typeof> yaoosl::parsing::instance::p_match_typeof(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::typeof>();
    std::shared_ptr<yaoosl::parsing::instance::typeof> fake;
    typeof_state state;
    resetable resetable2(*this);
    if (m_typeof_roundbrackedopen_typenavigation_roundbrackedclose_92(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_typeof_roundbrackedopen_typenavigation_roundbrackedclose_92(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_nameof_roundbrackedopen_expor_roundbrackedclose_93(bool is_can, std::shared_ptr<yaoosl::parsing::instance::nameof>& actual, yaoosl::parsing::instance::nameof_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__nameof(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_exp_or(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l9 = token__nameof(depth + 1).value();
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
    auto val12 = lr_match_exp_or(depth + 1);
    actual->value = val12;
    skip();
    auto l14 = token__round_bracked_close(depth + 1).value();
    for (;l14 != 0; l14--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_nameof(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::nameof> fake;
    nameof_state state;
    if (!m_nameof_roundbrackedopen_expor_roundbrackedclose_93(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::nameof> yaoosl::parsing::instance::p_match_nameof(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::nameof>();
    std::shared_ptr<yaoosl::parsing::instance::nameof> fake;
    nameof_state state;
    resetable resetable2(*this);
    if (m_nameof_roundbrackedopen_expor_roundbrackedclose_93(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_nameof_roundbrackedopen_expor_roundbrackedclose_93(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_typeof_94(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_typeof(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_typeof(depth + 1);
    actual->value = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_nameof_95(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_nameof(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_nameof(depth + 1);
    actual->value = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_scalar_96(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_scalar(depth + 1).value(), tok::SCALAR);
    actual->value = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_boolean_97(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token_boolean(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_boolean(depth + 1).value(), tok::BOOLEAN);
    actual->value = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_string_98(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_string(depth + 1).value(), tok::STRING);
    actual->value = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_integer_99(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_integer(depth + 1).value(), tok::INTEGER);
    actual->value = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives100(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_typeof_94(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_typeof_94(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_nameof_95(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_nameof_95(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_scalar_96(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_scalar_96(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_boolean_97(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_boolean_97(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_string_98(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_string_98(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_integer_99(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_integer_99(false, actual, state, depth + 1);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_exp_value(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_value> fake;
    exp_value_state state;
    if (!alternatives100(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::exp_value> yaoosl::parsing::instance::p_match_exp_value(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_value>();
    std::shared_ptr<yaoosl::parsing::instance::exp_value> fake;
    exp_value_state state;
    resetable resetable2(*this);
    if (alternatives100(true, fake, state, depth + 1))
    {
        resetable2.reset();
        alternatives100(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_roundbrackedopen_statement_roundbrackedclose_101(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_statement(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    return true;
}
bool yaoosl::parsing::instance::m_expchain_102(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_exp_chain(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_exp_chain(depth + 1);
    actual->value = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_call_103(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_call(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_call(depth + 1);
    actual->value = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expvalue_104(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_exp_value(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_exp_value(depth + 1);
    actual->value = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives105(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_roundbrackedopen_statement_roundbrackedclose_101(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_roundbrackedopen_statement_roundbrackedclose_101(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_expchain_102(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_expchain_102(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_call_103(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_call_103(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_expvalue_104(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_expvalue_104(false, actual, state, depth + 1);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_exp_nullar(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_nullar> fake;
    exp_nullar_state state;
    if (!alternatives105(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::exp_nullar> yaoosl::parsing::instance::p_match_exp_nullar(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_nullar>();
    std::shared_ptr<yaoosl::parsing::instance::exp_nullar> fake;
    exp_nullar_state state;
    resetable resetable2(*this);
    if (alternatives105(true, fake, state, depth + 1))
    {
        resetable2.reset();
        alternatives105(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_return_expor_106(bool is_can, std::shared_ptr<yaoosl::parsing::instance::return_statement>& actual, yaoosl::parsing::instance::return_statement_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_exp_or(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    actual->value = val6;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_return_statement(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::return_statement> fake;
    return_statement_state state;
    if (!m_return_expor_106(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::return_statement> yaoosl::parsing::instance::p_match_return_statement(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::return_statement>();
    std::shared_ptr<yaoosl::parsing::instance::return_statement> fake;
    return_statement_state state;
    resetable resetable2(*this);
    if (m_return_expor_106(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_return_expor_106(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_returnstatement_auto137_107(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_return_statement(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    auto l2 = token__auto_137(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = p_match_return_statement(depth + 1);
    actual->expression = val4;
    skip();
    auto l6 = token__auto_137(depth + 1).value();
    for (;l6 != 0; l6--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expression_auto137_108(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_expression(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    auto l2 = token__auto_137(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = lr_match_expression(depth + 1);
    actual->expression = val4;
    skip();
    auto l6 = token__auto_137(depth + 1).value();
    for (;l6 != 0; l6--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_auto137_109(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__auto_137(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__auto_137(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives110(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_returnstatement_auto137_107(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_returnstatement_auto137_107(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_expression_auto137_108(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_expression_auto137_108(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_auto137_109(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_auto137_109(false, actual, state, depth + 1);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_statement(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::statement> fake;
    statement_state state;
    if (!alternatives110(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::statement> yaoosl::parsing::instance::p_match_statement(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::statement>();
    std::shared_ptr<yaoosl::parsing::instance::statement> fake;
    statement_state state;
    resetable resetable2(*this);
    if (alternatives110(true, fake, state, depth + 1))
    {
        resetable2.reset();
        alternatives110(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_ident_111(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function_arg>& actual, yaoosl::parsing::instance::function_arg_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->name = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_function_arg(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::function_arg> fake;
    function_arg_state state;
    if (!m_ident_111(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::function_arg> yaoosl::parsing::instance::p_match_function_arg(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::function_arg>();
    std::shared_ptr<yaoosl::parsing::instance::function_arg> fake;
    function_arg_state state;
    resetable resetable2(*this);
    if (m_ident_111(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_ident_111(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_curlybrackedopen_112(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_open(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_curlybrackedclose_113(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_controlstructure_114(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_control_structure(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_control_structure(depth + 1);
    actual->body.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_statement_115(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_statement(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_statement(depth + 1);
    actual->body.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives116(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_controlstructure_114(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_controlstructure_114(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_statement_115(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_statement_115(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (!is_can)
    {
        report("Failed to match one of the following: { control-structure, statement }", depth);
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_curlybrackedclose_113(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::while117_118(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_curlybrackedclose_113(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives116(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_113(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives116(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives116(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_113(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_curlybrackedclose_119(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_scope(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::scope> fake;
    scope_state state;
    if (!m_curlybrackedopen_112(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!while117_118(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_curlybrackedclose_119(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::scope> yaoosl::parsing::instance::p_match_scope(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::scope>();
    std::shared_ptr<yaoosl::parsing::instance::scope> fake;
    scope_state state;
    resetable resetable2(*this);
    if (m_curlybrackedopen_112(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_curlybrackedopen_112(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (while117_118(true, fake, state, depth + 1))
    {
        resetable3.reset();
        while117_118(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (m_curlybrackedclose_119(true, fake, state, depth + 1))
    {
        resetable4.reset();
        m_curlybrackedclose_119(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_curlybrackedopen_120(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_open(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_curlybrackedopen_121(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_open(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_curlybrackedclose_122(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_controlstructure_123(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_control_structure(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_control_structure(depth + 1);
    actual->get_body.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_statement_124(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_statement(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_statement(depth + 1);
    actual->get_body.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives125(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_controlstructure_123(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_controlstructure_123(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_statement_124(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_statement_124(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (!is_can)
    {
        report("Failed to match one of the following: { control-structure, statement }", depth);
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_curlybrackedclose_122(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::while126_127(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_curlybrackedclose_122(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives125(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_122(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives125(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives125(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_122(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_curlybrackedclose_128(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_get_129(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__get(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__get(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    if (m_curlybrackedopen_121(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: { ({ Token: { ({)}) }", depth);
        return false;
    }
    while126_127(false, actual, state, depth + 1);
    if (m_curlybrackedclose_128(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: } ({ Token: } (})}) }", depth);
        return false;
    }
    return true;
}
bool yaoosl::parsing::instance::m_curlybrackedopen_130(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_open(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_curlybrackedclose_131(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_controlstructure_132(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_control_structure(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_control_structure(depth + 1);
    actual->set_body.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_statement_133(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_statement(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_statement(depth + 1);
    actual->set_body.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives134(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_controlstructure_132(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_controlstructure_132(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_statement_133(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_statement_133(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (!is_can)
    {
        report("Failed to match one of the following: { control-structure, statement }", depth);
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_curlybrackedclose_131(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::while135_136(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_curlybrackedclose_131(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives134(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_131(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives134(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives134(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_131(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_curlybrackedclose_137(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_set_138(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__set(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__set(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    if (m_curlybrackedopen_130(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: { ({ Token: { ({)}) }", depth);
        return false;
    }
    while135_136(false, actual, state, depth + 1);
    if (m_curlybrackedclose_137(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: } ({ Token: } (})}) }", depth);
        return false;
    }
    return true;
}
bool yaoosl::parsing::instance::alternatives139(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_get_129(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_get_129(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_set_138(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_set_138(false, actual, state, depth + 1);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_curlybrackedclose_140(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_scope_getset(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::scope_getset> fake;
    scope_getset_state state;
    if (!m_curlybrackedopen_120(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!alternatives139(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_curlybrackedclose_140(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::scope_getset> yaoosl::parsing::instance::p_match_scope_getset(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::scope_getset>();
    std::shared_ptr<yaoosl::parsing::instance::scope_getset> fake;
    scope_getset_state state;
    resetable resetable2(*this);
    if (m_curlybrackedopen_120(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_curlybrackedopen_120(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (alternatives139(true, fake, state, depth + 1))
    {
        resetable3.reset();
        alternatives139(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (m_curlybrackedclose_140(true, fake, state, depth + 1))
    {
        resetable4.reset();
        m_curlybrackedclose_140(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_func_ident_roundbrackedopen_141(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    return true;
}
bool yaoosl::parsing::instance::m_functionarg_142(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_function_arg(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    p_match_function_arg(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_functionarg_143(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_function_arg(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_function_arg(depth + 1);
    actual->args.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_roundbrackedclose_144(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_comma_functionarg_145(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_function_arg(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    return true;
}
bool yaoosl::parsing::instance::m_roundbrackedclose_144(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::while146_147(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_roundbrackedclose_144(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            if (m_comma_functionarg_145(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: , ({ Token: , (,)}), $ref: function-arg (XCG.Parsing.Production) }", depth);
                return false;
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_144(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (m_comma_functionarg_145(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: , ({ Token: , (,)}), $ref: function-arg (XCG.Parsing.Production) }", depth);
                return false;
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_144(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_functionarg_142(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_function_arg(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    p_match_function_arg(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::if148_149(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_functionarg_142(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_functionarg_143(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: function-arg (XCG.Parsing.Production) }", depth);
                return false;
            }
            while146_147(true, actual, state, depth + 1);
            return true;
        }
        return true;
    }
    else
    {
        if (cond2)
        {
            if (m_functionarg_143(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: function-arg (XCG.Parsing.Production) }", depth);
                return false;
            }
            while146_147(false, actual, state, depth + 1);
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_roundbrackedclose_scope_150(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_scope(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    return true;
}
bool yaoosl::parsing::instance::p_can_function(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::function> fake;
    function_state state;
    if (!m_func_ident_roundbrackedopen_141(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!if148_149(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_roundbrackedclose_scope_150(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::function> yaoosl::parsing::instance::p_match_function(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::function>();
    std::shared_ptr<yaoosl::parsing::instance::function> fake;
    function_state state;
    resetable resetable2(*this);
    if (m_func_ident_roundbrackedopen_141(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_func_ident_roundbrackedopen_141(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (if148_149(true, fake, state, depth + 1))
    {
        resetable3.reset();
        if148_149(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (m_roundbrackedclose_scope_150(true, fake, state, depth + 1))
    {
        resetable4.reset();
        m_roundbrackedclose_scope_150(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_scope_151(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure_body>& actual, yaoosl::parsing::instance::control_structure_body_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_scope(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_scope(depth + 1);
    actual->body = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_controlstructure_152(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure_body>& actual, yaoosl::parsing::instance::control_structure_body_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_control_structure(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_control_structure(depth + 1);
    actual->body = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_statement_153(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure_body>& actual, yaoosl::parsing::instance::control_structure_body_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_statement(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_statement(depth + 1);
    actual->body = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives154(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure_body>& actual, yaoosl::parsing::instance::control_structure_body_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_scope_151(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_scope_151(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_controlstructure_152(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_controlstructure_152(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_statement_153(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_statement_153(false, actual, state, depth + 1);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_control_structure_body(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::control_structure_body> fake;
    control_structure_body_state state;
    if (!alternatives154(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::control_structure_body> yaoosl::parsing::instance::p_match_control_structure_body(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::control_structure_body>();
    std::shared_ptr<yaoosl::parsing::instance::control_structure_body> fake;
    control_structure_body_state state;
    resetable resetable2(*this);
    if (alternatives154(true, fake, state, depth + 1))
    {
        resetable2.reset();
        alternatives154(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_while_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_155(bool is_can, std::shared_ptr<yaoosl::parsing::instance::while_loop>& actual, yaoosl::parsing::instance::while_loop_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_expression(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_control_structure_body(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    auto val12 = lr_match_expression(depth + 1);
    actual->condition = val12;
    skip();
    auto l14 = token__round_bracked_close(depth + 1).value();
    for (;l14 != 0; l14--)
    {
        next();
    }
    skip();
    auto val15 = p_match_control_structure_body(depth + 1);
    actual->body = val15;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_while_loop(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::while_loop> fake;
    while_loop_state state;
    if (!m_while_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_155(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::while_loop> yaoosl::parsing::instance::p_match_while_loop(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::while_loop>();
    std::shared_ptr<yaoosl::parsing::instance::while_loop> fake;
    while_loop_state state;
    resetable resetable2(*this);
    if (m_while_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_155(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_while_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_155(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_if_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_156(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_expression(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_control_structure_body(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    auto val12 = lr_match_expression(depth + 1);
    actual->condition = val12;
    skip();
    auto l14 = token__round_bracked_close(depth + 1).value();
    for (;l14 != 0; l14--)
    {
        next();
    }
    skip();
    auto val15 = p_match_control_structure_body(depth + 1);
    actual->if_body = val15;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_else_157(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__else(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_else_controlstructurebody_158(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_control_structure_body(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__else(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_control_structure_body(depth + 1);
    actual->else_body = val6;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_else_157(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__else(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::if159_160(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_else_157(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_else_controlstructurebody_158(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: else ({ Token: else (else)}), $ref: control-structure-body (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
    else
    {
        if (cond2)
        {
            if (m_else_controlstructurebody_158(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: else ({ Token: else (else)}), $ref: control-structure-body (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_if_else(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::if_else> fake;
    if_else_state state;
    if (!m_if_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_156(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!if159_160(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::if_else> yaoosl::parsing::instance::p_match_if_else(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::if_else>();
    std::shared_ptr<yaoosl::parsing::instance::if_else> fake;
    if_else_state state;
    resetable resetable2(*this);
    if (m_if_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_156(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_if_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_156(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (if159_160(true, fake, state, depth + 1))
    {
        resetable3.reset();
        if159_160(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_case_expvalue_colon_controlstructurebody_161(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_case>& actual, yaoosl::parsing::instance::switch_case_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__case(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_exp_value(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    auto l4 = token__colon(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_control_structure_body(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l7 = token__case(depth + 1).value();
    for (;l7 != 0; l7--)
    {
        next();
    }
    skip();
    auto val8 = p_match_exp_value(depth + 1);
    actual->value = val8;
    skip();
    auto l10 = token__colon(depth + 1).value();
    for (;l10 != 0; l10--)
    {
        next();
    }
    skip();
    auto val11 = p_match_control_structure_body(depth + 1);
    actual->body = val11;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_switch_case(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::switch_case> fake;
    switch_case_state state;
    if (!m_case_expvalue_colon_controlstructurebody_161(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::switch_case> yaoosl::parsing::instance::p_match_switch_case(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::switch_case>();
    std::shared_ptr<yaoosl::parsing::instance::switch_case> fake;
    switch_case_state state;
    resetable resetable2(*this);
    if (m_case_expvalue_colon_controlstructurebody_161(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_case_expvalue_colon_controlstructurebody_161(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_switch_roundbrackedopen_expression_roundbrackedclose_162(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__switch(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_expression(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l9 = token__switch(depth + 1).value();
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
    auto val12 = lr_match_expression(depth + 1);
    actual->value = val12;
    skip();
    auto l14 = token__round_bracked_close(depth + 1).value();
    for (;l14 != 0; l14--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_curlybrackedclose_163(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_switchcase_164(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_switch_case(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_switch_case(depth + 1);
    actual->part.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::if165_166(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = state.has_default.value();
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            report(" Multiple default cases found", depth);
            return true;
        }
        else
        {
            if (!is_can)
            {
                state.has_default = true;
            }
            return true;
        }
    }
    else
    {
        if (cond2)
        {
            report(" Multiple default cases found", depth);
            return true;
        }
        else
        {
            if (!is_can)
            {
                state.has_default = true;
            }
            return true;
        }
    }
}
bool yaoosl::parsing::instance::m_default_colon_controlstructurebody_167(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__default(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    auto l4 = token__colon(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_control_structure_body(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l7 = token__default(depth + 1).value();
    for (;l7 != 0; l7--)
    {
        next();
    }
    skip();
    auto l9 = token__colon(depth + 1).value();
    for (;l9 != 0; l9--)
    {
        next();
    }
    skip();
    auto val10 = p_match_control_structure_body(depth + 1);
    actual->default_body.push_back(val10);
    skip();
    if165_166(false, actual, state, depth + 1);
    return true;
}
bool yaoosl::parsing::instance::alternatives168(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_switchcase_164(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_switchcase_164(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_default_colon_controlstructurebody_167(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_default_colon_controlstructurebody_167(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (!is_can)
    {
        report("Failed to match one of the following: { switch-case, default, :, control-structure-body }", depth);
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_curlybrackedclose_163(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::while169_170(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_curlybrackedclose_163(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives168(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_163(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives168(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives168(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_163(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_curlybrackedclose_171(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_switch_(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::switch_> fake;
    switch__state state;
    if (!m_switch_roundbrackedopen_expression_roundbrackedclose_162(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!while169_170(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_curlybrackedclose_171(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::switch_> yaoosl::parsing::instance::p_match_switch_(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::switch_>();
    std::shared_ptr<yaoosl::parsing::instance::switch_> fake;
    switch__state state;
    resetable resetable2(*this);
    resetable resetable3(*this);
    if (m_switch_roundbrackedopen_expression_roundbrackedclose_162(true, fake, state, depth + 1))
    {
        resetable3.reset();
        m_switch_roundbrackedopen_expression_roundbrackedclose_162(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (while169_170(true, fake, state, depth + 1))
    {
        resetable4.reset();
        while169_170(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable5(*this);
    if (m_curlybrackedclose_171(true, fake, state, depth + 1))
    {
        resetable5.reset();
        m_curlybrackedclose_171(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_function_172(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_function(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_function(depth + 1);
    actual->content = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_whileloop_173(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_while_loop(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_while_loop(depth + 1);
    actual->content = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_ifelse_174(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_if_else(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_if_else(depth + 1);
    actual->content = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_switch_175(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_switch_(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_switch_(depth + 1);
    actual->content = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_scope_176(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_scope(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_scope(depth + 1);
    actual->content = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives177(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_function_172(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_function_172(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_whileloop_173(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_whileloop_173(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_ifelse_174(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_ifelse_174(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_switch_175(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_switch_175(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_scope_176(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_scope_176(false, actual, state, depth + 1);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_control_structure(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::control_structure> fake;
    control_structure_state state;
    if (!alternatives177(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::control_structure> yaoosl::parsing::instance::p_match_control_structure(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::control_structure>();
    std::shared_ptr<yaoosl::parsing::instance::control_structure> fake;
    control_structure_state state;
    resetable resetable2(*this);
    if (alternatives177(true, fake, state, depth + 1))
    {
        resetable2.reset();
        alternatives177(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_public_178(bool is_can, std::shared_ptr<yaoosl::parsing::instance::encapsulation>& actual, yaoosl::parsing::instance::encapsulation_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__public(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__public(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_local_179(bool is_can, std::shared_ptr<yaoosl::parsing::instance::encapsulation>& actual, yaoosl::parsing::instance::encapsulation_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__local(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__local(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_derived_180(bool is_can, std::shared_ptr<yaoosl::parsing::instance::encapsulation>& actual, yaoosl::parsing::instance::encapsulation_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__derived(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__derived(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_private_181(bool is_can, std::shared_ptr<yaoosl::parsing::instance::encapsulation>& actual, yaoosl::parsing::instance::encapsulation_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__private(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__private(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives182(bool is_can, std::shared_ptr<yaoosl::parsing::instance::encapsulation>& actual, yaoosl::parsing::instance::encapsulation_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_public_178(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_public_178(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_local_179(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_local_179(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_derived_180(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_derived_180(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_private_181(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_private_181(false, actual, state, depth + 1);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_encapsulation(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::encapsulation> fake;
    encapsulation_state state;
    if (!alternatives182(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::encapsulation> yaoosl::parsing::instance::p_match_encapsulation(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::encapsulation>();
    std::shared_ptr<yaoosl::parsing::instance::encapsulation> fake;
    encapsulation_state state;
    resetable resetable2(*this);
    if (alternatives182(true, fake, state, depth + 1))
    {
        resetable2.reset();
        alternatives182(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_namespace_identnavigation_183(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__namespace(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_ident_navigation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__namespace(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_ident_navigation(depth + 1);
    actual->name = val6;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_curlybrackedopen_184(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_open(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_curlybrackedclose_185(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_namespace_186(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_namespace_(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_namespace_(depth + 1);
    actual->contents.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_conversion_187(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_conversion(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_conversion(depth + 1);
    actual->contents.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_class_188(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_class_(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_class_(depth + 1);
    actual->contents.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_method_189(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_method(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_method(depth + 1);
    actual->contents.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives190(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_namespace_186(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_namespace_186(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_conversion_187(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_conversion_187(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_class_188(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_class_188(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_method_189(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_method_189(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (!is_can)
    {
        report("Failed to match one of the following: { namespace, conversion, class, method }", depth);
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_curlybrackedclose_185(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::while191_192(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_curlybrackedclose_185(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives190(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_185(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives190(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives190(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_185(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_curlybrackedclose_193(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_namespace_(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::namespace_> fake;
    namespace__state state;
    if (!m_namespace_identnavigation_183(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_curlybrackedopen_184(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!while191_192(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_curlybrackedclose_193(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::namespace_> yaoosl::parsing::instance::p_match_namespace_(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::namespace_>();
    std::shared_ptr<yaoosl::parsing::instance::namespace_> fake;
    namespace__state state;
    resetable resetable2(*this);
    if (m_namespace_identnavigation_183(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_namespace_identnavigation_183(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (m_curlybrackedopen_184(true, fake, state, depth + 1))
    {
        resetable3.reset();
        m_curlybrackedopen_184(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (while191_192(true, fake, state, depth + 1))
    {
        resetable4.reset();
        while191_192(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable5(*this);
    if (m_curlybrackedclose_193(true, fake, state, depth + 1))
    {
        resetable5.reset();
        m_curlybrackedclose_193(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_encapsulation_class_ident_194(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_encapsulation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    auto l2 = token__class(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val6 = p_match_encapsulation(depth + 1);
    actual->scope = val6;
    skip();
    auto l8 = token__class(depth + 1).value();
    for (;l8 != 0; l8--)
    {
        next();
    }
    skip();
    auto val9 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->name = val9;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_curlybrackedopen_195(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_open(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_curlybrackedclose_196(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_conversion_197(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_conversion(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_conversion(depth + 1);
    actual->contents.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_class_198(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_class_(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_class_(depth + 1);
    actual->contents.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_constructor_199(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_constructor(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_constructor(depth + 1);
    actual->contents.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_destructor_200(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_destructor(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_destructor(depth + 1);
    actual->contents.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_copystructor_201(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_copystructor(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_copystructor(depth + 1);
    actual->contents.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_method_202(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_method(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_method(depth + 1);
    actual->contents.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_property_203(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_property(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_property(depth + 1);
    actual->contents.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_indexer_204(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_indexer(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_indexer(depth + 1);
    actual->contents.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives205(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_conversion_197(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_conversion_197(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_class_198(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_class_198(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_constructor_199(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_constructor_199(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_destructor_200(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_destructor_200(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_copystructor_201(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_copystructor_201(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_method_202(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_method_202(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_property_203(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_property_203(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_indexer_204(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_indexer_204(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (!is_can)
    {
        report("Failed to match one of the following: { conversion, class, constructor, destructor, copystructor, method, property, indexer }", depth);
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_curlybrackedclose_196(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::while206_207(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_curlybrackedclose_196(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives205(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_196(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives205(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives205(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_196(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_curlybrackedclose_208(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_class_(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::class_> fake;
    class__state state;
    if (!m_encapsulation_class_ident_194(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_curlybrackedopen_195(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!while206_207(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_curlybrackedclose_208(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::class_> yaoosl::parsing::instance::p_match_class_(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::class_>();
    std::shared_ptr<yaoosl::parsing::instance::class_> fake;
    class__state state;
    resetable resetable2(*this);
    if (m_encapsulation_class_ident_194(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_encapsulation_class_ident_194(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (m_curlybrackedopen_195(true, fake, state, depth + 1))
    {
        resetable3.reset();
        m_curlybrackedopen_195(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (while206_207(true, fake, state, depth + 1))
    {
        resetable4.reset();
        while206_207(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable5(*this);
    if (m_curlybrackedclose_208(true, fake, state, depth + 1))
    {
        resetable5.reset();
        m_curlybrackedclose_208(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_typenavigation_ident_209(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item>& actual, yaoosl::parsing::instance::method_arglist_item_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_type_navigation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = lr_match_type_navigation(depth + 1);
    actual->type = val4;
    skip();
    auto val5 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->name = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_equal_210(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item>& actual, yaoosl::parsing::instance::method_arglist_item_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__equal(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__equal(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_equal_expvalue_211(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item>& actual, yaoosl::parsing::instance::method_arglist_item_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__equal(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_exp_value(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__equal(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_exp_value(depth + 1);
    actual->value = val6;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_equal_210(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item>& actual, yaoosl::parsing::instance::method_arglist_item_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__equal(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__equal(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::if212_213(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item>& actual, yaoosl::parsing::instance::method_arglist_item_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_equal_210(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_equal_expvalue_211(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: = ({ Token: = (=)}), $ref: exp-value (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
    else
    {
        if (cond2)
        {
            if (m_equal_expvalue_211(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: = ({ Token: = (=)}), $ref: exp-value (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_method_arglist_item(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::method_arglist_item> fake;
    method_arglist_item_state state;
    if (!m_typenavigation_ident_209(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!if212_213(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::method_arglist_item> yaoosl::parsing::instance::p_match_method_arglist_item(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::method_arglist_item>();
    std::shared_ptr<yaoosl::parsing::instance::method_arglist_item> fake;
    method_arglist_item_state state;
    resetable resetable2(*this);
    if (m_typenavigation_ident_209(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_typenavigation_ident_209(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (if212_213(true, fake, state, depth + 1))
    {
        resetable3.reset();
        if212_213(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_roundbrackedopen_214(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_open(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_methodarglistitem_215(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_method_arglist_item(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    p_match_method_arglist_item(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_methodarglistitem_216(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_method_arglist_item(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_method_arglist_item(depth + 1);
    actual->args.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_roundbrackedclose_217(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_comma_methodarglistitem_218(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_method_arglist_item(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_method_arglist_item(depth + 1);
    actual->args.push_back(val6);
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives219(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_comma_methodarglistitem_218(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_comma_methodarglistitem_218(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (!is_can)
    {
        report("Failed to match one of the following: { ,, method-arglist-item }", depth);
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_roundbrackedclose_217(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::while220_221(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_roundbrackedclose_217(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives219(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_217(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives219(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives219(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_217(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_comma_222(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_comma_223(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_comma_222(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::if224_225(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_comma_222(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_comma_223(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: , ({ Token: , (,)}) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
    else
    {
        if (cond2)
        {
            if (m_comma_223(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: , ({ Token: , (,)}) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_methodarglistitem_215(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_method_arglist_item(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    p_match_method_arglist_item(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::if226_227(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_methodarglistitem_215(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_methodarglistitem_216(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: method-arglist-item (XCG.Parsing.Production) }", depth);
                return false;
            }
            while220_221(true, actual, state, depth + 1);
            if224_225(true, actual, state, depth + 1);
            return true;
        }
        return true;
    }
    else
    {
        if (cond2)
        {
            if (m_methodarglistitem_216(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: method-arglist-item (XCG.Parsing.Production) }", depth);
                return false;
            }
            while220_221(false, actual, state, depth + 1);
            if224_225(false, actual, state, depth + 1);
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_roundbrackedclose_228(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_method_arglist(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::method_arglist> fake;
    method_arglist_state state;
    if (!m_roundbrackedopen_214(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!if226_227(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_roundbrackedclose_228(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::method_arglist> yaoosl::parsing::instance::p_match_method_arglist(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::method_arglist>();
    std::shared_ptr<yaoosl::parsing::instance::method_arglist> fake;
    method_arglist_state state;
    resetable resetable2(*this);
    if (m_roundbrackedopen_214(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_roundbrackedopen_214(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (if226_227(true, fake, state, depth + 1))
    {
        resetable3.reset();
        if226_227(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (m_roundbrackedclose_228(true, fake, state, depth + 1))
    {
        resetable4.reset();
        m_roundbrackedclose_228(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_roundbrackedopen_229(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_open(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_methodarglistitem_230(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_method_arglist_item(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_method_arglist_item(depth + 1);
    actual->args.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_roundbrackedclose_231(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_comma_methodarglistitem_232(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_method_arglist_item(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_method_arglist_item(depth + 1);
    actual->args.push_back(val6);
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives233(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_comma_methodarglistitem_232(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_comma_methodarglistitem_232(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (!is_can)
    {
        report("Failed to match one of the following: { ,, method-arglist-item }", depth);
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_roundbrackedclose_231(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::while234_235(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_roundbrackedclose_231(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives233(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_231(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives233(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives233(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_231(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_comma_236(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_comma_237(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_comma_236(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::if238_239(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_comma_236(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_comma_237(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: , ({ Token: , (,)}) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
    else
    {
        if (cond2)
        {
            if (m_comma_237(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: , ({ Token: , (,)}) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_roundbrackedclose_240(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_close(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_method_arglist_non_empty(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty> fake;
    method_arglist_non_empty_state state;
    if (!m_roundbrackedopen_229(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_methodarglistitem_230(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!while234_235(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!if238_239(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_roundbrackedclose_240(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty> yaoosl::parsing::instance::p_match_method_arglist_non_empty(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::method_arglist_non_empty>();
    std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty> fake;
    method_arglist_non_empty_state state;
    resetable resetable2(*this);
    if (m_roundbrackedopen_229(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_roundbrackedopen_229(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (m_methodarglistitem_230(true, fake, state, depth + 1))
    {
        resetable3.reset();
        m_methodarglistitem_230(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (while234_235(true, fake, state, depth + 1))
    {
        resetable4.reset();
        while234_235(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable5(*this);
    if (if238_239(true, fake, state, depth + 1))
    {
        resetable5.reset();
        if238_239(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable6(*this);
    if (m_roundbrackedclose_240(true, fake, state, depth + 1))
    {
        resetable6.reset();
        m_roundbrackedclose_240(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_ident_241(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_ident>& actual, yaoosl::parsing::instance::method_ident_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->name = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_templatedefinition_242(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_ident>& actual, yaoosl::parsing::instance::method_ident_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_template_definition(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    p_match_template_definition(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_templatedefinition_243(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_ident>& actual, yaoosl::parsing::instance::method_ident_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_template_definition(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_template_definition(depth + 1);
    actual->template_ = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_templatedefinition_242(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_ident>& actual, yaoosl::parsing::instance::method_ident_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_template_definition(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    p_match_template_definition(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::if244_245(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_ident>& actual, yaoosl::parsing::instance::method_ident_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_templatedefinition_242(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_templatedefinition_243(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: template-definition (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
    else
    {
        if (cond2)
        {
            if (m_templatedefinition_243(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: template-definition (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_method_ident(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::method_ident> fake;
    method_ident_state state;
    if (!m_ident_241(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!if244_245(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::method_ident> yaoosl::parsing::instance::p_match_method_ident(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::method_ident>();
    std::shared_ptr<yaoosl::parsing::instance::method_ident> fake;
    method_ident_state state;
    resetable resetable2(*this);
    if (m_ident_241(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_ident_241(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (if244_245(true, fake, state, depth + 1))
    {
        resetable3.reset();
        if244_245(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_encapsulation_246(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_encapsulation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_encapsulation(depth + 1);
    actual->encaps = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_unbound_247(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__unbound(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__unbound(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_unbound_248(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__unbound(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__unbound(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_unbound_247(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__unbound(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__unbound(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::if249_250(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_unbound_247(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_unbound_248(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: unbound ({ Token: unbound (unbound)}) }", depth);
                return false;
            }
            if (!is_can)
            {
                actual->is_static = true;
            }
            return true;
        }
        return true;
    }
    else
    {
        if (cond2)
        {
            if (m_unbound_248(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: unbound ({ Token: unbound (unbound)}) }", depth);
                return false;
            }
            if (!is_can)
            {
                actual->is_static = true;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_typenavigation_methodident_methodarglist_scope_251(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_type_navigation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_method_ident(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_method_arglist(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_scope(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_type_navigation(depth + 1);
    actual->return_type = val2;
    skip();
    auto val3 = p_match_method_ident(depth + 1);
    actual->ident = val3;
    skip();
    auto val4 = p_match_method_arglist(depth + 1);
    actual->arglist = val4;
    skip();
    auto val5 = p_match_scope(depth + 1);
    actual->body = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_method(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::method> fake;
    method_state state;
    if (!m_encapsulation_246(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!if249_250(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_typenavigation_methodident_methodarglist_scope_251(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::method> yaoosl::parsing::instance::p_match_method(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::method>();
    std::shared_ptr<yaoosl::parsing::instance::method> fake;
    method_state state;
    resetable resetable2(*this);
    if (m_encapsulation_246(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_encapsulation_246(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (if249_250(true, fake, state, depth + 1))
    {
        resetable3.reset();
        if249_250(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (m_typenavigation_methodident_methodarglist_scope_251(true, fake, state, depth + 1))
    {
        resetable4.reset();
        m_typenavigation_methodident_methodarglist_scope_251(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_encapsulation_typenavigation_methodident_methodarglist_scope_252(bool is_can, std::shared_ptr<yaoosl::parsing::instance::constructor>& actual, yaoosl::parsing::instance::constructor_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_encapsulation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_type_navigation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_method_ident(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_method_arglist(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_scope(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_encapsulation(depth + 1);
    actual->encaps = val2;
    skip();
    auto val3 = lr_match_type_navigation(depth + 1);
    actual->return_type = val3;
    skip();
    auto val4 = p_match_method_ident(depth + 1);
    actual->ident = val4;
    skip();
    auto val5 = p_match_method_arglist(depth + 1);
    actual->arglist = val5;
    skip();
    auto val6 = p_match_scope(depth + 1);
    actual->body = val6;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_constructor(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::constructor> fake;
    constructor_state state;
    if (!m_encapsulation_typenavigation_methodident_methodarglist_scope_252(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::constructor> yaoosl::parsing::instance::p_match_constructor(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::constructor>();
    std::shared_ptr<yaoosl::parsing::instance::constructor> fake;
    constructor_state state;
    resetable resetable2(*this);
    if (m_encapsulation_typenavigation_methodident_methodarglist_scope_252(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_encapsulation_typenavigation_methodident_methodarglist_scope_252(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_encapsulation_typenavigation_tilde_methodident_methodarglist_scope_253(bool is_can, std::shared_ptr<yaoosl::parsing::instance::destructor>& actual, yaoosl::parsing::instance::destructor_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_encapsulation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_type_navigation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    auto l2 = token__tilde(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_method_ident(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_method_arglist(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_scope(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = p_match_encapsulation(depth + 1);
    actual->encaps = val4;
    skip();
    auto val5 = lr_match_type_navigation(depth + 1);
    actual->return_type = val5;
    skip();
    auto l7 = token__tilde(depth + 1).value();
    for (;l7 != 0; l7--)
    {
        next();
    }
    skip();
    auto val8 = p_match_method_ident(depth + 1);
    actual->ident = val8;
    skip();
    auto val9 = p_match_method_arglist(depth + 1);
    actual->arglist = val9;
    skip();
    auto val10 = p_match_scope(depth + 1);
    actual->body = val10;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_destructor(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::destructor> fake;
    destructor_state state;
    if (!m_encapsulation_typenavigation_tilde_methodident_methodarglist_scope_253(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::destructor> yaoosl::parsing::instance::p_match_destructor(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::destructor>();
    std::shared_ptr<yaoosl::parsing::instance::destructor> fake;
    destructor_state state;
    resetable resetable2(*this);
    if (m_encapsulation_typenavigation_tilde_methodident_methodarglist_scope_253(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_encapsulation_typenavigation_tilde_methodident_methodarglist_scope_253(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_encapsulation_typenavigation_plus_methodident_methodarglist_254(bool is_can, std::shared_ptr<yaoosl::parsing::instance::copystructor>& actual, yaoosl::parsing::instance::copystructor_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_encapsulation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_type_navigation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_method_ident(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_method_arglist(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = p_match_encapsulation(depth + 1);
    actual->encaps = val4;
    skip();
    auto val5 = lr_match_type_navigation(depth + 1);
    actual->return_type = val5;
    skip();
    auto l7 = token_plus(depth + 1).value();
    for (;l7 != 0; l7--)
    {
        next();
    }
    skip();
    auto val8 = p_match_method_ident(depth + 1);
    actual->ident = val8;
    skip();
    auto val9 = p_match_method_arglist(depth + 1);
    actual->arglist = val9;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_scope_255(bool is_can, std::shared_ptr<yaoosl::parsing::instance::copystructor>& actual, yaoosl::parsing::instance::copystructor_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_scope(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_scope(depth + 1);
    actual->body = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_equal_delete_256(bool is_can, std::shared_ptr<yaoosl::parsing::instance::copystructor>& actual, yaoosl::parsing::instance::copystructor_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__equal(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    auto l4 = token__delete(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l7 = token__equal(depth + 1).value();
    for (;l7 != 0; l7--)
    {
        next();
    }
    skip();
    auto l9 = token__delete(depth + 1).value();
    for (;l9 != 0; l9--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives257(bool is_can, std::shared_ptr<yaoosl::parsing::instance::copystructor>& actual, yaoosl::parsing::instance::copystructor_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_scope_255(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_scope_255(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_equal_delete_256(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_equal_delete_256(false, actual, state, depth + 1);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_copystructor(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::copystructor> fake;
    copystructor_state state;
    if (!m_encapsulation_typenavigation_plus_methodident_methodarglist_254(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!alternatives257(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::copystructor> yaoosl::parsing::instance::p_match_copystructor(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::copystructor>();
    std::shared_ptr<yaoosl::parsing::instance::copystructor> fake;
    copystructor_state state;
    resetable resetable2(*this);
    if (m_encapsulation_typenavigation_plus_methodident_methodarglist_254(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_encapsulation_typenavigation_plus_methodident_methodarglist_254(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (alternatives257(true, fake, state, depth + 1))
    {
        resetable3.reset();
        alternatives257(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_encapsulation_conversion_typenavigation_roundbrackedopen_typenavigation_ident_roundbrackedclose_scope_258(bool is_can, std::shared_ptr<yaoosl::parsing::instance::conversion>& actual, yaoosl::parsing::instance::conversion_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_encapsulation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    auto l2 = token__conversion(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_type_navigation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_type_navigation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    auto l6 = token_ident(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    auto l8 = token__round_bracked_close(depth + 1);
    if (l8.has_value())
    {
        for (auto i9 = l8.value(); i9 != 0; i9--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_scope(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val10 = p_match_encapsulation(depth + 1);
    actual->encaps = val10;
    skip();
    auto l12 = token__conversion(depth + 1).value();
    for (;l12 != 0; l12--)
    {
        next();
    }
    skip();
    auto val13 = lr_match_type_navigation(depth + 1);
    actual->target_type = val13;
    skip();
    auto l15 = token__round_bracked_open(depth + 1).value();
    for (;l15 != 0; l15--)
    {
        next();
    }
    skip();
    auto val16 = lr_match_type_navigation(depth + 1);
    actual->source_type = val16;
    skip();
    auto val17 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->name = val17;
    skip();
    auto l19 = token__round_bracked_close(depth + 1).value();
    for (;l19 != 0; l19--)
    {
        next();
    }
    skip();
    auto val20 = p_match_scope(depth + 1);
    actual->body = val20;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_conversion(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::conversion> fake;
    conversion_state state;
    if (!m_encapsulation_conversion_typenavigation_roundbrackedopen_typenavigation_ident_roundbrackedclose_scope_258(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::conversion> yaoosl::parsing::instance::p_match_conversion(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::conversion>();
    std::shared_ptr<yaoosl::parsing::instance::conversion> fake;
    conversion_state state;
    resetable resetable2(*this);
    if (m_encapsulation_conversion_typenavigation_roundbrackedopen_typenavigation_ident_roundbrackedclose_scope_258(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_encapsulation_conversion_typenavigation_roundbrackedopen_typenavigation_ident_roundbrackedclose_scope_258(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_encapsulation_typenavigation_259(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_encapsulation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_type_navigation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_encapsulation(depth + 1);
    actual->encaps = val2;
    skip();
    auto val3 = lr_match_type_navigation(depth + 1);
    actual->target_type = val3;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_templatedefinition_260(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_template_definition(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    p_match_template_definition(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_templatedefinition_261(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_template_definition(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_template_definition(depth + 1);
    actual->template_ = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_templatedefinition_260(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_template_definition(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    p_match_template_definition(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::if262_263(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_templatedefinition_260(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_templatedefinition_261(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: template-definition (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
    else
    {
        if (cond2)
        {
            if (m_templatedefinition_261(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: template-definition (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_squarebrackedopen_methodarglistnonempty_squarebrackedclose_scopegetset_264(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__square_bracked_open(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_method_arglist_non_empty(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    auto l4 = token__square_bracked_close(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_scope_getset(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l7 = token__square_bracked_open(depth + 1).value();
    for (;l7 != 0; l7--)
    {
        next();
    }
    skip();
    auto val8 = p_match_method_arglist_non_empty(depth + 1);
    actual->arglist = val8;
    skip();
    auto l10 = token__square_bracked_close(depth + 1).value();
    for (;l10 != 0; l10--)
    {
        next();
    }
    skip();
    auto val11 = p_match_scope_getset(depth + 1);
    actual->body = val11;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_indexer(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::indexer> fake;
    indexer_state state;
    if (!m_encapsulation_typenavigation_259(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!if262_263(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_squarebrackedopen_methodarglistnonempty_squarebrackedclose_scopegetset_264(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::indexer> yaoosl::parsing::instance::p_match_indexer(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::indexer>();
    std::shared_ptr<yaoosl::parsing::instance::indexer> fake;
    indexer_state state;
    resetable resetable2(*this);
    if (m_encapsulation_typenavigation_259(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_encapsulation_typenavigation_259(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (if262_263(true, fake, state, depth + 1))
    {
        resetable3.reset();
        if262_263(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (m_squarebrackedopen_methodarglistnonempty_squarebrackedclose_scopegetset_264(true, fake, state, depth + 1))
    {
        resetable4.reset();
        m_squarebrackedopen_methodarglistnonempty_squarebrackedclose_scopegetset_264(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_encapsulation_typenavigation_ident_auto137_265(bool is_can, std::shared_ptr<yaoosl::parsing::instance::property>& actual, yaoosl::parsing::instance::property_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_encapsulation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_type_navigation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    auto l4 = token__auto_137(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val6 = p_match_encapsulation(depth + 1);
    actual->encaps = val6;
    skip();
    auto val7 = lr_match_type_navigation(depth + 1);
    actual->target_type = val7;
    skip();
    auto val8 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->name = val8;
    skip();
    auto l10 = token__auto_137(depth + 1).value();
    for (;l10 != 0; l10--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_encapsulation_typenavigation_ident_scopegetset_266(bool is_can, std::shared_ptr<yaoosl::parsing::instance::property>& actual, yaoosl::parsing::instance::property_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_encapsulation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_type_navigation(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_scope_getset(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = p_match_encapsulation(depth + 1);
    actual->encaps = val4;
    skip();
    auto val5 = lr_match_type_navigation(depth + 1);
    actual->target_type = val5;
    skip();
    auto val6 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->name = val6;
    skip();
    auto val7 = p_match_scope_getset(depth + 1);
    actual->body = val7;
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives267(bool is_can, std::shared_ptr<yaoosl::parsing::instance::property>& actual, yaoosl::parsing::instance::property_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_encapsulation_typenavigation_ident_auto137_265(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_encapsulation_typenavigation_ident_auto137_265(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_encapsulation_typenavigation_ident_scopegetset_266(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_encapsulation_typenavigation_ident_scopegetset_266(false, actual, state, depth + 1);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_property(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::property> fake;
    property_state state;
    if (!alternatives267(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::property> yaoosl::parsing::instance::p_match_property(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::property>();
    std::shared_ptr<yaoosl::parsing::instance::property> fake;
    property_state state;
    resetable resetable2(*this);
    if (alternatives267(true, fake, state, depth + 1))
    {
        resetable2.reset();
        alternatives267(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_namespace_268(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_namespace_(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_namespace_(depth + 1);
    actual->contents.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_conversion_269(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_conversion(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_conversion(depth + 1);
    actual->contents.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_class_270(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_class_(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_class_(depth + 1);
    actual->contents.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_method_271(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_method(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_method(depth + 1);
    actual->contents.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives272(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_namespace_268(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_namespace_268(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_conversion_269(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_conversion_269(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_class_270(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_class_270(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_method_271(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_method_271(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (!is_can)
    {
        report("Failed to match one of the following: { namespace, conversion, class, method }", depth);
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::while273_274(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = current() == '\0';
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives272(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = current() == '\0';
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives272(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives272(true, actual, state, depth + 1))
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
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_main(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::main> fake;
    main_state state;
    if (!while273_274(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::main> yaoosl::parsing::instance::p_match_main(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::main>();
    std::shared_ptr<yaoosl::parsing::instance::main> fake;
    main_state state;
    resetable resetable2(*this);
    if (while273_274(true, fake, state, depth + 1))
    {
        resetable2.reset();
        while273_274(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expchain_expchaincall_275(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain>& actual, yaoosl::parsing::instance::exp_chain_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_exp_chain_call(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_exp_chain_call(depth + 1);
    actual->right = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expchain_expchainaccess_276(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain>& actual, yaoosl::parsing::instance::exp_chain_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_exp_chain_access(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_exp_chain_access(depth + 1);
    actual->right = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expchain_expchainindexer_277(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain>& actual, yaoosl::parsing::instance::exp_chain_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_exp_chain_indexer(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_exp_chain_indexer(depth + 1);
    actual->right = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expchainstart_278(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain>& actual, yaoosl::parsing::instance::exp_chain_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_exp_chain_start(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_exp_chain_start(depth + 1);
    actual->left = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_chain(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_chain> fake;
    exp_chain_state state;
    if (!m_expchainstart_278(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expchain_expchaincall_275(true, fake, state, depth + 1))
        {
        }
        else if (m_expchain_expchainaccess_276(true, fake, state, depth + 1))
        {
        }
        else if (m_expchain_expchainindexer_277(true, fake, state, depth + 1))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_chain> yaoosl::parsing::instance::lr_match_exp_chain(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_chain>();
    std::shared_ptr<yaoosl::parsing::instance::exp_chain> fake;
    exp_chain_state state;
    if (!m_expchainstart_278(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expchain_expchaincall_275(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_chain>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expchain_expchaincall_275(false, actual, state, depth + 1);
        }
        else if (m_expchain_expchainaccess_276(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_chain>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expchain_expchainaccess_276(false, actual, state, depth + 1);
        }
        else if (m_expchain_expchainindexer_277(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_chain>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expchain_expchainindexer_277(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_identnavigation_dot_ident_279(bool is_can, std::shared_ptr<yaoosl::parsing::instance::ident_navigation>& actual, yaoosl::parsing::instance::ident_navigation_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__dot(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l7 = token__dot(depth + 1).value();
    for (;l7 != 0; l7--)
    {
        next();
    }
    skip();
    auto val8 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->right = val8;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_ident_280(bool is_can, std::shared_ptr<yaoosl::parsing::instance::ident_navigation>& actual, yaoosl::parsing::instance::ident_navigation_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->left = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_ident_navigation(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::ident_navigation> fake;
    ident_navigation_state state;
    if (!m_ident_280(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_identnavigation_dot_ident_279(true, fake, state, depth + 1))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::ident_navigation> yaoosl::parsing::instance::lr_match_ident_navigation(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::ident_navigation>();
    std::shared_ptr<yaoosl::parsing::instance::ident_navigation> fake;
    ident_navigation_state state;
    if (!m_ident_280(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_identnavigation_dot_ident_279(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::ident_navigation>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_identnavigation_dot_ident_279(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_typenavigation_dot_ident_templateusage_281(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_navigation>& actual, yaoosl::parsing::instance::type_navigation_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__dot(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_template_usage(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l7 = token__dot(depth + 1).value();
    for (;l7 != 0; l7--)
    {
        next();
    }
    skip();
    auto val8 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->right = val8;
    skip();
    auto val9 = p_match_template_usage(depth + 1);
    actual->template_ = val9;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_typenavigation_dot_ident_282(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_navigation>& actual, yaoosl::parsing::instance::type_navigation_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__dot(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l7 = token__dot(depth + 1).value();
    for (;l7 != 0; l7--)
    {
        next();
    }
    skip();
    auto val8 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->right = val8;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_ident_283(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_navigation>& actual, yaoosl::parsing::instance::type_navigation_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->left = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_type_navigation(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::type_navigation> fake;
    type_navigation_state state;
    if (!m_ident_283(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_typenavigation_dot_ident_templateusage_281(true, fake, state, depth + 1))
        {
        }
        else if (m_typenavigation_dot_ident_282(true, fake, state, depth + 1))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::type_navigation> yaoosl::parsing::instance::lr_match_type_navigation(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::type_navigation>();
    std::shared_ptr<yaoosl::parsing::instance::type_navigation> fake;
    type_navigation_state state;
    if (!m_ident_283(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_typenavigation_dot_ident_templateusage_281(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::type_navigation>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_typenavigation_dot_ident_templateusage_281(false, actual, state, depth + 1);
        }
        else if (m_typenavigation_dot_ident_282(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::type_navigation>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_typenavigation_dot_ident_282(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_exparithmetic2_slash_expnullar_284(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_exp_nullar(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    return true;
}
bool yaoosl::parsing::instance::m_exparithmetic2_star_expnullar_285(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (p_can_exp_nullar(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    return true;
}
bool yaoosl::parsing::instance::m_expnullar_286(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_exp_nullar(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_exp_nullar(depth + 1);
    actual->left = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_arithmetic_2(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> fake;
    exp_arithmetic_2_state state;
    if (!m_expnullar_286(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic2_slash_expnullar_284(true, fake, state, depth + 1))
        {
        }
        else if (m_exparithmetic2_star_expnullar_285(true, fake, state, depth + 1))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> yaoosl::parsing::instance::lr_match_exp_arithmetic_2(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_2>();
    std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> fake;
    exp_arithmetic_2_state state;
    if (!m_expnullar_286(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic2_slash_expnullar_284(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_2>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic2_slash_expnullar_284(false, actual, state, depth + 1);
        }
        else if (m_exparithmetic2_star_expnullar_285(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_2>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic2_star_expnullar_285(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_exparithmetic1_plus_exparithmetic2_287(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_exp_arithmetic_2(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    return true;
}
bool yaoosl::parsing::instance::m_exparithmetic1_minus_exparithmetic2_288(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_exp_arithmetic_2(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    return true;
}
bool yaoosl::parsing::instance::m_exparithmetic2_289(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_exp_arithmetic_2(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_exp_arithmetic_2(depth + 1);
    actual->left = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_arithmetic_1(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> fake;
    exp_arithmetic_1_state state;
    if (!m_exparithmetic2_289(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic1_plus_exparithmetic2_287(true, fake, state, depth + 1))
        {
        }
        else if (m_exparithmetic1_minus_exparithmetic2_288(true, fake, state, depth + 1))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> yaoosl::parsing::instance::lr_match_exp_arithmetic_1(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_1>();
    std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> fake;
    exp_arithmetic_1_state state;
    if (!m_exparithmetic2_289(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic1_plus_exparithmetic2_287(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_1>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic1_plus_exparithmetic2_287(false, actual, state, depth + 1);
        }
        else if (m_exparithmetic1_minus_exparithmetic2_288(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_1>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic1_minus_exparithmetic2_288(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expcompare_lessthenequal_exparithmetic1_290(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_exp_arithmetic_1(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    return true;
}
bool yaoosl::parsing::instance::m_expcompare_lessthen_exparithmetic1_291(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_exp_arithmetic_1(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    return true;
}
bool yaoosl::parsing::instance::m_expcompare_greaterthenequal_exparithmetic1_292(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_exp_arithmetic_1(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    return true;
}
bool yaoosl::parsing::instance::m_expcompare_greaterthen_exparithmetic1_293(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_exp_arithmetic_1(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    return true;
}
bool yaoosl::parsing::instance::m_exparithmetic1_294(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_exp_arithmetic_1(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_exp_arithmetic_1(depth + 1);
    actual->left = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_compare(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_compare> fake;
    exp_compare_state state;
    if (!m_exparithmetic1_294(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expcompare_lessthenequal_exparithmetic1_290(true, fake, state, depth + 1))
        {
        }
        else if (m_expcompare_lessthen_exparithmetic1_291(true, fake, state, depth + 1))
        {
        }
        else if (m_expcompare_greaterthenequal_exparithmetic1_292(true, fake, state, depth + 1))
        {
        }
        else if (m_expcompare_greaterthen_exparithmetic1_293(true, fake, state, depth + 1))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_compare> yaoosl::parsing::instance::lr_match_exp_compare(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
    std::shared_ptr<yaoosl::parsing::instance::exp_compare> fake;
    exp_compare_state state;
    if (!m_exparithmetic1_294(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expcompare_lessthenequal_exparithmetic1_290(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_lessthenequal_exparithmetic1_290(false, actual, state, depth + 1);
        }
        else if (m_expcompare_lessthen_exparithmetic1_291(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_lessthen_exparithmetic1_291(false, actual, state, depth + 1);
        }
        else if (m_expcompare_greaterthenequal_exparithmetic1_292(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_greaterthenequal_exparithmetic1_292(false, actual, state, depth + 1);
        }
        else if (m_expcompare_greaterthen_exparithmetic1_293(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_greaterthen_exparithmetic1_293(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expequality_lessthenequal_expcompare_295(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_exp_compare(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    return true;
}
bool yaoosl::parsing::instance::m_expequality_lessthen_expcompare_296(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_exp_compare(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    return true;
}
bool yaoosl::parsing::instance::m_expequality_greaterthenequal_expcompare_297(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_exp_compare(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    return true;
}
bool yaoosl::parsing::instance::m_expequality_greaterthen_expcompare_298(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_exp_compare(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    return true;
}
bool yaoosl::parsing::instance::m_expcompare_299(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_exp_compare(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_exp_compare(depth + 1);
    actual->left = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_equality(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_equality> fake;
    exp_equality_state state;
    if (!m_expcompare_299(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expequality_lessthenequal_expcompare_295(true, fake, state, depth + 1))
        {
        }
        else if (m_expequality_lessthen_expcompare_296(true, fake, state, depth + 1))
        {
        }
        else if (m_expequality_greaterthenequal_expcompare_297(true, fake, state, depth + 1))
        {
        }
        else if (m_expequality_greaterthen_expcompare_298(true, fake, state, depth + 1))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_equality> yaoosl::parsing::instance::lr_match_exp_equality(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
    std::shared_ptr<yaoosl::parsing::instance::exp_equality> fake;
    exp_equality_state state;
    if (!m_expcompare_299(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expequality_lessthenequal_expcompare_295(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_lessthenequal_expcompare_295(false, actual, state, depth + 1);
        }
        else if (m_expequality_lessthen_expcompare_296(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_lessthen_expcompare_296(false, actual, state, depth + 1);
        }
        else if (m_expequality_greaterthenequal_expcompare_297(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_greaterthenequal_expcompare_297(false, actual, state, depth + 1);
        }
        else if (m_expequality_greaterthen_expcompare_298(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_greaterthen_expcompare_298(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expand_and_expequality_300(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and>& actual, yaoosl::parsing::instance::exp_and_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_exp_equality(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
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
    return true;
}
bool yaoosl::parsing::instance::m_expequality_301(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and>& actual, yaoosl::parsing::instance::exp_and_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_exp_equality(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_exp_equality(depth + 1);
    actual->left = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_and(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_and> fake;
    exp_and_state state;
    if (!m_expequality_301(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expand_and_expequality_300(true, fake, state, depth + 1))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_and> yaoosl::parsing::instance::lr_match_exp_and(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_and>();
    std::shared_ptr<yaoosl::parsing::instance::exp_and> fake;
    exp_and_state state;
    if (!m_expequality_301(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expand_and_expequality_300(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_and>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expand_and_expequality_300(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expor_or_expand_302(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or>& actual, yaoosl::parsing::instance::exp_or_state& state, size_t depth)
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_exp_and(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__or(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_and(depth + 1);
    actual->right = val6;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expequality_303(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or>& actual, yaoosl::parsing::instance::exp_or_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_exp_equality(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_exp_equality(depth + 1);
    actual->left = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_or(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_or> fake;
    exp_or_state state;
    if (!m_expequality_303(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expor_or_expand_302(true, fake, state, depth + 1))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_or> yaoosl::parsing::instance::lr_match_exp_or(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_or>();
    std::shared_ptr<yaoosl::parsing::instance::exp_or> fake;
    exp_or_state state;
    if (!m_expequality_303(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expor_or_expand_302(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_or>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expor_or_expand_302(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expression_equal_expression_304(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expression>& actual, yaoosl::parsing::instance::expression_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__equal(depth + 1);
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
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (lr_can_expression(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__equal(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_expression(depth + 1);
    actual->value = val6;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expor_305(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expression>& actual, yaoosl::parsing::instance::expression_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_exp_or(depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_exp_or(depth + 1);
    actual->value = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_expression(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::expression> fake;
    expression_state state;
    if (!m_expor_305(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expression_equal_expression_304(true, fake, state, depth + 1))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::expression> yaoosl::parsing::instance::lr_match_expression(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::expression>();
    std::shared_ptr<yaoosl::parsing::instance::expression> fake;
    expression_state state;
    if (!m_expor_305(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expression_equal_expression_304(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::expression>();
                actual->value = tmp_actual3;
            }
            is_first2 = false;
            m_expression_equal_expression_304(false, actual, state, depth + 1);
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<template_usage_item> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("template_usage_item:");
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->key.line) + "; C" + std::to_string(node->key.column) + "; O" + std::to_string(node->key.offset) + ") `" + std::string(contents.substr(node->key.offset, node->key.length).begin(), contents.substr(node->key.offset, node->key.length).end()) + "`");
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<template_usage> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("template_usage:");
    for (auto element : node->items)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [items]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<template_definition_item> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("template_definition_item:");
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->key.line) + "; C" + std::to_string(node->key.column) + "; O" + std::to_string(node->key.offset) + ") `" + std::string(contents.substr(node->key.offset, node->key.length).begin(), contents.substr(node->key.offset, node->key.length).end()) + "`");
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<template_definition> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("template_definition:");
    for (auto element : node->items)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [items]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_chain_start> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_chain_start:");
    switch (node->part.index())
    {
        case 0:
        output.push_back(std::string("  ") + "token (L" + std::to_string(std::get<token>(node->part).line) + "; C" + std::to_string(std::get<token>(node->part).column) + "; O" + std::to_string(std::get<token>(node->part).offset) + ") `" + std::string(contents.substr(std::get<token>(node->part).offset, std::get<token>(node->part).length).begin(), contents.substr(std::get<token>(node->part).offset, std::get<token>(node->part).length).end()) + "`");
        break;
        case 1:
        if (std::get<std::shared_ptr<call>>(node->part))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<call>>(node->part), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [part]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_chain_indexer> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_chain_indexer:");
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_chain_access> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_chain_access:");
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->capture40.line) + "; C" + std::to_string(node->capture40.column) + "; O" + std::to_string(node->capture40.offset) + ") `" + std::string(contents.substr(node->capture40.offset, node->capture40.length).begin(), contents.substr(node->capture40.offset, node->capture40.length).end()) + "`");
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_chain_call> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_chain_call:");
    if (node->capture42)
    {
        auto lines = create_string_tree(node->capture42, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [capture42]" "\u001b[0m" : line));
            first = false;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<typeof> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("typeof:");
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<nameof> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("nameof:");
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_value> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_value:");
    switch (node->value.index())
    {
        case 0:
        if (std::get<std::shared_ptr<typeof>>(node->value))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<typeof>>(node->value), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [value]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<nameof>>(node->value))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<nameof>>(node->value), contents);
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_nullar> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_nullar:");
    switch (node->value.index())
    {
        case 0:
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
        case 1:
        if (std::get<std::shared_ptr<exp_chain>>(node->value))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_chain>>(node->value), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [value]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 2:
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
        case 3:
        if (std::get<std::shared_ptr<exp_value>>(node->value))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_value>>(node->value), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [value]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<return_statement> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("return_statement:");
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<scope_getset> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("scope_getset:");
    for (auto element : node->get_body)
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
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [get_body]" "\u001b[0m" : line));
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
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [get_body]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
        }
    }
    for (auto element : node->set_body)
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
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [set_body]" "\u001b[0m" : line));
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
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [set_body]" "\u001b[0m" : line));
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<control_structure_body> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("control_structure_body:");
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
    if (node->if_body)
    {
        auto lines = create_string_tree(node->if_body, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [if_body]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->else_body)
    {
        auto lines = create_string_tree(node->else_body, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [else_body]" "\u001b[0m" : line));
            first = false;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<switch_case> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("switch_case:");
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<switch_> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("switch_:");
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
    for (auto element : node->part)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [part]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    for (auto element : node->default_body)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [default_body]" "\u001b[0m" : line));
                first = false;
            }
        }
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
        if (std::get<std::shared_ptr<switch_>>(node->content))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<switch_>>(node->content), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [content]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 4:
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<encapsulation> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("encapsulation:");
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<namespace_> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("namespace_:");
    if (node->name)
    {
        auto lines = create_string_tree(node->name, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [name]" "\u001b[0m" : line));
            first = false;
        }
    }
    for (auto element : node->contents)
    {
        switch (element.index())
        {
            case 0:
            if (std::get<std::shared_ptr<namespace_>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<namespace_>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [contents]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
            case 1:
            if (std::get<std::shared_ptr<conversion>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<conversion>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [contents]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
            case 2:
            if (std::get<std::shared_ptr<class_>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<class_>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [contents]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
            case 3:
            if (std::get<std::shared_ptr<method>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<method>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [contents]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<class_> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("class_:");
    if (node->scope)
    {
        auto lines = create_string_tree(node->scope, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [scope]" "\u001b[0m" : line));
            first = false;
        }
    }
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->name.line) + "; C" + std::to_string(node->name.column) + "; O" + std::to_string(node->name.offset) + ") `" + std::string(contents.substr(node->name.offset, node->name.length).begin(), contents.substr(node->name.offset, node->name.length).end()) + "`");
    for (auto element : node->contents)
    {
        switch (element.index())
        {
            case 0:
            if (std::get<std::shared_ptr<conversion>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<conversion>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [contents]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
            case 1:
            if (std::get<std::shared_ptr<class_>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<class_>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [contents]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
            case 2:
            if (std::get<std::shared_ptr<constructor>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<constructor>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [contents]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
            case 3:
            if (std::get<std::shared_ptr<destructor>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<destructor>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [contents]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
            case 4:
            if (std::get<std::shared_ptr<copystructor>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<copystructor>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [contents]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
            case 5:
            if (std::get<std::shared_ptr<method>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<method>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [contents]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
            case 6:
            if (std::get<std::shared_ptr<property>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<property>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [contents]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
            case 7:
            if (std::get<std::shared_ptr<indexer>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<indexer>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [contents]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<method_arglist_item> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("method_arglist_item:");
    if (node->type)
    {
        auto lines = create_string_tree(node->type, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [type]" "\u001b[0m" : line));
            first = false;
        }
    }
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<method_arglist> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("method_arglist:");
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<method_arglist_non_empty> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("method_arglist_non_empty:");
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<method_ident> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("method_ident:");
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->name.line) + "; C" + std::to_string(node->name.column) + "; O" + std::to_string(node->name.offset) + ") `" + std::string(contents.substr(node->name.offset, node->name.length).begin(), contents.substr(node->name.offset, node->name.length).end()) + "`");
    if (node->template_)
    {
        auto lines = create_string_tree(node->template_, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [template_]" "\u001b[0m" : line));
            first = false;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<method> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("method:");
    if (node->is_static.has_value())
    {
        output.push_back(std::string("  ") + std::to_string(node->is_static.value()));
    }
    if (node->encaps)
    {
        auto lines = create_string_tree(node->encaps, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [encaps]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->return_type)
    {
        auto lines = create_string_tree(node->return_type, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [return_type]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->ident)
    {
        auto lines = create_string_tree(node->ident, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [ident]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->arglist)
    {
        auto lines = create_string_tree(node->arglist, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [arglist]" "\u001b[0m" : line));
            first = false;
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<constructor> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("constructor:");
    if (node->encaps)
    {
        auto lines = create_string_tree(node->encaps, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [encaps]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->return_type)
    {
        auto lines = create_string_tree(node->return_type, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [return_type]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->ident)
    {
        auto lines = create_string_tree(node->ident, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [ident]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->arglist)
    {
        auto lines = create_string_tree(node->arglist, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [arglist]" "\u001b[0m" : line));
            first = false;
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<destructor> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("destructor:");
    if (node->encaps)
    {
        auto lines = create_string_tree(node->encaps, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [encaps]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->return_type)
    {
        auto lines = create_string_tree(node->return_type, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [return_type]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->ident)
    {
        auto lines = create_string_tree(node->ident, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [ident]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->arglist)
    {
        auto lines = create_string_tree(node->arglist, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [arglist]" "\u001b[0m" : line));
            first = false;
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<copystructor> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("copystructor:");
    if (node->encaps)
    {
        auto lines = create_string_tree(node->encaps, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [encaps]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->return_type)
    {
        auto lines = create_string_tree(node->return_type, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [return_type]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->ident)
    {
        auto lines = create_string_tree(node->ident, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [ident]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->arglist)
    {
        auto lines = create_string_tree(node->arglist, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [arglist]" "\u001b[0m" : line));
            first = false;
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<conversion> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("conversion:");
    if (node->encaps)
    {
        auto lines = create_string_tree(node->encaps, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [encaps]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->target_type)
    {
        auto lines = create_string_tree(node->target_type, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [target_type]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->source_type)
    {
        auto lines = create_string_tree(node->source_type, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [source_type]" "\u001b[0m" : line));
            first = false;
        }
    }
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->name.line) + "; C" + std::to_string(node->name.column) + "; O" + std::to_string(node->name.offset) + ") `" + std::string(contents.substr(node->name.offset, node->name.length).begin(), contents.substr(node->name.offset, node->name.length).end()) + "`");
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<indexer> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("indexer:");
    if (node->encaps)
    {
        auto lines = create_string_tree(node->encaps, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [encaps]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->target_type)
    {
        auto lines = create_string_tree(node->target_type, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [target_type]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->template_)
    {
        auto lines = create_string_tree(node->template_, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [template_]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->arglist)
    {
        auto lines = create_string_tree(node->arglist, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [arglist]" "\u001b[0m" : line));
            first = false;
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<property> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("property:");
    if (node->encaps)
    {
        auto lines = create_string_tree(node->encaps, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [encaps]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->target_type)
    {
        auto lines = create_string_tree(node->target_type, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [target_type]" "\u001b[0m" : line));
            first = false;
        }
    }
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->name.line) + "; C" + std::to_string(node->name.column) + "; O" + std::to_string(node->name.offset) + ") `" + std::string(contents.substr(node->name.offset, node->name.length).begin(), contents.substr(node->name.offset, node->name.length).end()) + "`");
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<main> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("main:");
    for (auto element : node->contents)
    {
        switch (element.index())
        {
            case 0:
            if (std::get<std::shared_ptr<namespace_>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<namespace_>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [contents]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
            case 1:
            if (std::get<std::shared_ptr<conversion>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<conversion>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [contents]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
            case 2:
            if (std::get<std::shared_ptr<class_>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<class_>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [contents]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
            case 3:
            if (std::get<std::shared_ptr<method>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<method>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [contents]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_chain> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_chain:");
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_chain>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_chain>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_chain_start>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_chain_start>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    switch (node->right.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_chain_call>>(node->right))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_chain_call>>(node->right), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [right]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_chain_access>>(node->right))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_chain_access>>(node->right), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [right]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 2:
        if (std::get<std::shared_ptr<exp_chain_indexer>>(node->right))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_chain_indexer>>(node->right), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [right]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<ident_navigation> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("ident_navigation:");
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<ident_navigation>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<ident_navigation>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        output.push_back(std::string("  ") + "token (L" + std::to_string(std::get<token>(node->left).line) + "; C" + std::to_string(std::get<token>(node->left).column) + "; O" + std::to_string(std::get<token>(node->left).offset) + ") `" + std::string(contents.substr(std::get<token>(node->left).offset, std::get<token>(node->left).length).begin(), contents.substr(std::get<token>(node->left).offset, std::get<token>(node->left).length).end()) + "`");
        break;
    }
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->right.line) + "; C" + std::to_string(node->right.column) + "; O" + std::to_string(node->right.offset) + ") `" + std::string(contents.substr(node->right.offset, node->right.length).begin(), contents.substr(node->right.offset, node->right.length).end()) + "`");
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<type_navigation> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("type_navigation:");
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<type_navigation>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<type_navigation>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        output.push_back(std::string("  ") + "token (L" + std::to_string(std::get<token>(node->left).line) + "; C" + std::to_string(std::get<token>(node->left).column) + "; O" + std::to_string(std::get<token>(node->left).offset) + ") `" + std::string(contents.substr(std::get<token>(node->left).offset, std::get<token>(node->left).length).begin(), contents.substr(std::get<token>(node->left).offset, std::get<token>(node->left).length).end()) + "`");
        break;
    }
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->right.line) + "; C" + std::to_string(node->right.column) + "; O" + std::to_string(node->right.offset) + ") `" + std::string(contents.substr(node->right.offset, node->right.length).begin(), contents.substr(node->right.offset, node->right.length).end()) + "`");
    if (node->template_)
    {
        auto lines = create_string_tree(node->template_, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [template_]" "\u001b[0m" : line));
            first = false;
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<expression> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("expression:");
    if (node->assign_to)
    {
        auto lines = create_string_tree(node->assign_to, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [assign_to]" "\u001b[0m" : line));
            first = false;
        }
    }
    switch (node->value.index())
    {
        case 0:
        if (std::get<std::shared_ptr<expression>>(node->value))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<expression>>(node->value), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [value]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_or>>(node->value))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_or>>(node->value), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [value]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    return output;
}
