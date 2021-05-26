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
std::optional<size_t> yaoosl::parsing::instance::token_true_(size_t depth)
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
std::optional<size_t> yaoosl::parsing::instance::token_false_(size_t depth)
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
        std::optional<size_t> res3 = token_true_(depth + 1);
        if (res3.has_value())
        {
            count2++;
            for (size_t i = 0; i < res3; i++)
            {
                next();
            }
            continue;
        }
        std::optional<size_t> res4 = token_false_(depth + 1);
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
        if (current() == '\"')
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
        if (current() != '\"')
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
        if (current() == '\"')
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
std::optional<size_t> yaoosl::parsing::instance::token__exclamation(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == '!')
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
    auto resultVariable24 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable24;
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
    auto resultVariable25 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable25;
}
std::optional<size_t> yaoosl::parsing::instance::token__less_then_less_then(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "<<";
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
    auto resultVariable26 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable26;
}
std::optional<size_t> yaoosl::parsing::instance::token__greater_then_greater_then(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = ">>";
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
std::optional<size_t> yaoosl::parsing::instance::token__less_then_less_then_less_then(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "<<<";
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
    auto resultVariable28 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable28;
}
std::optional<size_t> yaoosl::parsing::instance::token__greater_then_greater_then_greater_then(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = ">>>";
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
    auto resultVariable29 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable29;
}
std::optional<size_t> yaoosl::parsing::instance::token__ampersand(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == '&')
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
std::optional<size_t> yaoosl::parsing::instance::token__vertical_bar(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if (current() == '|')
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
    auto resultVariable32 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable32;
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
    auto resultVariable33 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable33;
}
std::optional<size_t> yaoosl::parsing::instance::token__ampersand_ampersand(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "&&";
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
    auto resultVariable34 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable34;
}
std::optional<size_t> yaoosl::parsing::instance::token__vertical_bar_vertical_bar(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "||";
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
    auto resultVariable35 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable35;
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
    auto resultVariable36 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable36;
}
std::optional<size_t> yaoosl::parsing::instance::token__semicolon(size_t depth)
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
    auto resultVariable37 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable37;
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
    auto resultVariable38 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable38;
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
    auto resultVariable39 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable39;
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
    auto resultVariable40 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable40;
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
    auto resultVariable41 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable41;
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
    auto resultVariable42 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable42;
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
    auto resultVariable43 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable43;
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
    auto resultVariable44 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable44;
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
    auto resultVariable45 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable45;
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
    auto resultVariable46 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable46;
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
    auto resultVariable47 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable47;
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
    auto resultVariable48 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable48;
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
    auto resultVariable49 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable49;
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
    auto resultVariable50 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable50;
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
    auto resultVariable51 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable51;
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
    auto resultVariable52 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable52;
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
    auto resultVariable53 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable53;
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
    auto resultVariable54 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable54;
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
    auto resultVariable55 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable55;
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
    auto resultVariable56 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable56;
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
    auto resultVariable57 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable57;
}
std::optional<size_t> yaoosl::parsing::instance::token__operator(size_t depth)
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "operator";
        if (m_contents.length() - m_offset >= 8 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 8, str3, str3 + 8))
        {
            count2++;
            for (size_t i = 0; i < 8; i++)
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
    auto resultVariable58 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable58;
}
bool yaoosl::parsing::instance::m_ident_roundbrackedopen_59(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_expression_60(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_expression_61(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_roundbrackedclose_62(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_comma_expression_63(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_comma_64(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
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
bool yaoosl::parsing::instance::alternatives65(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_comma_expression_63(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_comma_expression_63(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_comma_64(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_comma_64(false, actual, state, depth + 1);
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
bool yaoosl::parsing::instance::while66_67(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_roundbrackedclose_62(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives65(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_62(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives65(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives65(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_62(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::if68_69(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_expression_60(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_expression_61(true, actual, state, depth + 1))
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
            while66_67(true, actual, state, depth + 1);
            return true;
        }
        return true;
    }
    else
    {
        if (cond2)
        {
            if (m_expression_61(false, actual, state, depth + 1))
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
            while66_67(false, actual, state, depth + 1);
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_roundbrackedclose_70(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth)
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
    if (!m_ident_roundbrackedopen_59(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!if68_69(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_roundbrackedclose_70(true, fake, state, depth + 1))
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
    if (m_ident_roundbrackedopen_59(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_ident_roundbrackedopen_59(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (if68_69(true, fake, state, depth + 1))
    {
        resetable3.reset();
        if68_69(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (m_roundbrackedclose_70(true, fake, state, depth + 1))
    {
        resetable4.reset();
        m_roundbrackedclose_70(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_ident_71(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage_item>& actual, yaoosl::parsing::instance::template_usage_item_state& state, size_t depth)
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
    if (!m_ident_71(true, fake, state, depth + 1))
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
    if (m_ident_71(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_ident_71(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_lessthen_72(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_templateusageitem_73(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_comma_74(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_comma_templateusageitem_75(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth)
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
bool yaoosl::parsing::instance::alternatives76(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_comma_templateusageitem_75(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_comma_templateusageitem_75(false, actual, state, depth + 1);
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
bool yaoosl::parsing::instance::while77_78(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_comma_74(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (cond3 && current() != '\0')
        {
            while (!alternatives76(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_comma_74(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (cond3 && current() != '\0')
        {
            if (!alternatives76(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives76(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_comma_74(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_greaterthen_79(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth)
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
    if (!m_lessthen_72(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_templateusageitem_73(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!while77_78(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_greaterthen_79(true, fake, state, depth + 1))
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
    if (m_lessthen_72(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_lessthen_72(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (m_templateusageitem_73(true, fake, state, depth + 1))
    {
        resetable3.reset();
        m_templateusageitem_73(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (while77_78(true, fake, state, depth + 1))
    {
        resetable4.reset();
        while77_78(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable5(*this);
    if (m_greaterthen_79(true, fake, state, depth + 1))
    {
        resetable5.reset();
        m_greaterthen_79(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_ident_80(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition_item>& actual, yaoosl::parsing::instance::template_definition_item_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_equal_81(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition_item>& actual, yaoosl::parsing::instance::template_definition_item_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_equal_expvalue_82(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition_item>& actual, yaoosl::parsing::instance::template_definition_item_state& state, size_t depth)
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
bool yaoosl::parsing::instance::if83_84(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition_item>& actual, yaoosl::parsing::instance::template_definition_item_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_equal_81(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_equal_expvalue_82(true, actual, state, depth + 1))
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
            if (m_equal_expvalue_82(false, actual, state, depth + 1))
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
    if (!m_ident_80(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!if83_84(true, fake, state, depth + 1))
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
    if (m_ident_80(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_ident_80(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (if83_84(true, fake, state, depth + 1))
    {
        resetable3.reset();
        if83_84(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_lessthen_85(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_templatedefinitionitem_86(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_comma_87(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_comma_templatedefinitionitem_88(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth)
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
bool yaoosl::parsing::instance::alternatives89(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_comma_templatedefinitionitem_88(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_comma_templatedefinitionitem_88(false, actual, state, depth + 1);
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
bool yaoosl::parsing::instance::while90_91(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_comma_87(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (cond3 && current() != '\0')
        {
            while (!alternatives89(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_comma_87(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (cond3 && current() != '\0')
        {
            if (!alternatives89(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives89(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_comma_87(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_greaterthen_92(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth)
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
    if (!m_lessthen_85(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_templatedefinitionitem_86(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!while90_91(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_greaterthen_92(true, fake, state, depth + 1))
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
    if (m_lessthen_85(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_lessthen_85(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (m_templatedefinitionitem_86(true, fake, state, depth + 1))
    {
        resetable3.reset();
        m_templatedefinitionitem_86(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (while90_91(true, fake, state, depth + 1))
    {
        resetable4.reset();
        while90_91(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable5(*this);
    if (m_greaterthen_92(true, fake, state, depth + 1))
    {
        resetable5.reset();
        m_greaterthen_92(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_call_93(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_start>& actual, yaoosl::parsing::instance::exp_chain_start_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_ident_94(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_start>& actual, yaoosl::parsing::instance::exp_chain_start_state& state, size_t depth)
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
bool yaoosl::parsing::instance::alternatives95(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_start>& actual, yaoosl::parsing::instance::exp_chain_start_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_call_93(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_call_93(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_ident_94(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_ident_94(false, actual, state, depth + 1);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_exp_chain_start(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_chain_start> fake;
    exp_chain_start_state state;
    if (!alternatives95(true, fake, state, depth + 1))
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
    if (alternatives95(true, fake, state, depth + 1))
    {
        resetable2.reset();
        alternatives95(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_squarebrackedopen_96(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_indexer>& actual, yaoosl::parsing::instance::exp_chain_indexer_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_squarebrackedclose_97(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_indexer>& actual, yaoosl::parsing::instance::exp_chain_indexer_state& state, size_t depth)
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
    if (!m_squarebrackedopen_96(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_squarebrackedclose_97(true, fake, state, depth + 1))
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
    if (m_squarebrackedopen_96(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_squarebrackedopen_96(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (m_squarebrackedclose_97(true, fake, state, depth + 1))
    {
        resetable3.reset();
        m_squarebrackedclose_97(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_dot_ident_98(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_access>& actual, yaoosl::parsing::instance::exp_chain_access_state& state, size_t depth)
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
    if (!m_dot_ident_98(true, fake, state, depth + 1))
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
    if (m_dot_ident_98(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_dot_ident_98(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_dot_call_99(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_call>& actual, yaoosl::parsing::instance::exp_chain_call_state& state, size_t depth)
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
    if (!m_dot_call_99(true, fake, state, depth + 1))
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
    if (m_dot_call_99(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_dot_call_99(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_typenavigation_squarebrackedopen_expvalue_squarebrackedclose_100(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_match>& actual, yaoosl::parsing::instance::type_match_state& state, size_t depth)
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
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val6 = lr_match_type_navigation(depth + 1);
    actual->base = val6;
    skip();
    auto l8 = token__square_bracked_open(depth + 1).value();
    for (;l8 != 0; l8--)
    {
        next();
    }
    skip();
    auto val9 = p_match_exp_value(depth + 1);
    actual->array_size = val9;
    skip();
    auto l11 = token__square_bracked_close(depth + 1).value();
    for (;l11 != 0; l11--)
    {
        next();
    }
    skip();
    if (!is_can)
    {
        actual->is_array = true;
    }
    return true;
}
bool yaoosl::parsing::instance::m_typenavigation_squarebrackedopen_squarebrackedclose_101(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_match>& actual, yaoosl::parsing::instance::type_match_state& state, size_t depth)
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
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val6 = lr_match_type_navigation(depth + 1);
    actual->base = val6;
    skip();
    auto l8 = token__square_bracked_open(depth + 1).value();
    for (;l8 != 0; l8--)
    {
        next();
    }
    skip();
    auto l10 = token__square_bracked_close(depth + 1).value();
    for (;l10 != 0; l10--)
    {
        next();
    }
    skip();
    if (!is_can)
    {
        actual->is_array = true;
    }
    return true;
}
bool yaoosl::parsing::instance::m_typenavigation_102(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_match>& actual, yaoosl::parsing::instance::type_match_state& state, size_t depth)
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
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_type_navigation(depth + 1);
    actual->base = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives103(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_match>& actual, yaoosl::parsing::instance::type_match_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_typenavigation_squarebrackedopen_expvalue_squarebrackedclose_100(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_typenavigation_squarebrackedopen_expvalue_squarebrackedclose_100(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_typenavigation_squarebrackedopen_squarebrackedclose_101(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_typenavigation_squarebrackedopen_squarebrackedclose_101(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_typenavigation_102(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_typenavigation_102(false, actual, state, depth + 1);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_type_match(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::type_match> fake;
    type_match_state state;
    if (!alternatives103(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::type_match> yaoosl::parsing::instance::p_match_type_match(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::type_match>();
    std::shared_ptr<yaoosl::parsing::instance::type_match> fake;
    type_match_state state;
    resetable resetable2(*this);
    if (alternatives103(true, fake, state, depth + 1))
    {
        resetable2.reset();
        alternatives103(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_typeof_roundbrackedopen_typematch_roundbrackedclose_104(bool is_can, std::shared_ptr<yaoosl::parsing::instance::typeof>& actual, yaoosl::parsing::instance::typeof_state& state, size_t depth)
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
    if (p_can_type_match(depth + 1))
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
    auto val12 = p_match_type_match(depth + 1);
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
    if (!m_typeof_roundbrackedopen_typematch_roundbrackedclose_104(true, fake, state, depth + 1))
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
    if (m_typeof_roundbrackedopen_typematch_roundbrackedclose_104(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_typeof_roundbrackedopen_typematch_roundbrackedclose_104(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_nameof_roundbrackedopen_expor_roundbrackedclose_105(bool is_can, std::shared_ptr<yaoosl::parsing::instance::nameof>& actual, yaoosl::parsing::instance::nameof_state& state, size_t depth)
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
    if (!m_nameof_roundbrackedopen_expor_roundbrackedclose_105(true, fake, state, depth + 1))
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
    if (m_nameof_roundbrackedopen_expor_roundbrackedclose_105(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_nameof_roundbrackedopen_expor_roundbrackedclose_105(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_ident_string_ident_106(bool is_can, std::shared_ptr<yaoosl::parsing::instance::string_literal>& actual, yaoosl::parsing::instance::string_literal_state& state, size_t depth)
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
    auto l4 = token_string(depth + 1);
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
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val8 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->prefix = val8;
    skip();
    auto val9 = create_token(token_string(depth + 1).value(), tok::STRING);
    actual->value = val9;
    skip();
    auto val10 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->postfix = val10;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_string_ident_107(bool is_can, std::shared_ptr<yaoosl::parsing::instance::string_literal>& actual, yaoosl::parsing::instance::string_literal_state& state, size_t depth)
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
    auto val6 = create_token(token_string(depth + 1).value(), tok::STRING);
    actual->value = val6;
    skip();
    auto val7 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->postfix = val7;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_ident_string_108(bool is_can, std::shared_ptr<yaoosl::parsing::instance::string_literal>& actual, yaoosl::parsing::instance::string_literal_state& state, size_t depth)
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
    auto l4 = token_string(depth + 1);
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
    actual->prefix = val6;
    skip();
    auto val7 = create_token(token_string(depth + 1).value(), tok::STRING);
    actual->value = val7;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_string_109(bool is_can, std::shared_ptr<yaoosl::parsing::instance::string_literal>& actual, yaoosl::parsing::instance::string_literal_state& state, size_t depth)
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
bool yaoosl::parsing::instance::alternatives110(bool is_can, std::shared_ptr<yaoosl::parsing::instance::string_literal>& actual, yaoosl::parsing::instance::string_literal_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_ident_string_ident_106(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_ident_string_ident_106(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_string_ident_107(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_string_ident_107(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_ident_string_108(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_ident_string_108(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_string_109(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_string_109(false, actual, state, depth + 1);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_string_literal(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::string_literal> fake;
    string_literal_state state;
    if (!alternatives110(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::string_literal> yaoosl::parsing::instance::p_match_string_literal(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::string_literal>();
    std::shared_ptr<yaoosl::parsing::instance::string_literal> fake;
    string_literal_state state;
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
bool yaoosl::parsing::instance::m_typeof_111(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth)
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
    actual->type = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_nameof_112(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth)
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
    actual->name = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_scalar_113(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth)
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
    actual->float_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_boolean_114(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth)
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
    actual->bool_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_stringliteral_115(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_string_literal(depth + 1))
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
    auto val2 = p_match_string_literal(depth + 1);
    actual->string = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_integer_116(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth)
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
    actual->int_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives117(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_typeof_111(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_typeof_111(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_nameof_112(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_nameof_112(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_scalar_113(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_scalar_113(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_boolean_114(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_boolean_114(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_stringliteral_115(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_stringliteral_115(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_integer_116(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_integer_116(false, actual, state, depth + 1);
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
    if (!alternatives117(true, fake, state, depth + 1))
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
    if (alternatives117(true, fake, state, depth + 1))
    {
        resetable2.reset();
        alternatives117(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_roundbrackedopen_statement_roundbrackedclose_118(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_declaration_119(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_declaration(depth + 1))
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
    auto val2 = p_match_declaration(depth + 1);
    actual->value = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expchain_120(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_expvalue_121(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth)
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
bool yaoosl::parsing::instance::alternatives122(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_roundbrackedopen_statement_roundbrackedclose_118(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_roundbrackedopen_statement_roundbrackedclose_118(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_declaration_119(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_declaration_119(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_expchain_120(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_expchain_120(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_expvalue_121(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_expvalue_121(false, actual, state, depth + 1);
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
    if (!alternatives122(true, fake, state, depth + 1))
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
    if (alternatives122(true, fake, state, depth + 1))
    {
        resetable2.reset();
        alternatives122(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_exclamation_expunary_123(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_unary>& actual, yaoosl::parsing::instance::exp_unary_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__exclamation(depth + 1);
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
    if (p_can_exp_unary(depth + 1))
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
    auto val4 = create_token(token__exclamation(depth + 1).value(), tok::_EXCLAMATION);
    actual->operator_ = val4;
    skip();
    auto val5 = p_match_exp_unary(depth + 1);
    actual->value = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_tilde_expunary_124(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_unary>& actual, yaoosl::parsing::instance::exp_unary_state& state, size_t depth)
{
    resetable resetable1(*this);
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
    if (p_can_exp_unary(depth + 1))
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
    auto val4 = create_token(token__tilde(depth + 1).value(), tok::_TILDE);
    actual->operator_ = val4;
    skip();
    auto val5 = p_match_exp_unary(depth + 1);
    actual->value = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_minus_expunary_125(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_unary>& actual, yaoosl::parsing::instance::exp_unary_state& state, size_t depth)
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
    if (p_can_exp_unary(depth + 1))
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
    auto val4 = create_token(token_minus(depth + 1).value(), tok::MINUS);
    actual->operator_ = val4;
    skip();
    auto val5 = p_match_exp_unary(depth + 1);
    actual->value = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_plus_expunary_126(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_unary>& actual, yaoosl::parsing::instance::exp_unary_state& state, size_t depth)
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
    if (p_can_exp_unary(depth + 1))
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
    auto val4 = create_token(token_plus(depth + 1).value(), tok::PLUS);
    actual->operator_ = val4;
    skip();
    auto val5 = p_match_exp_unary(depth + 1);
    actual->value = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expnullar_127(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_unary>& actual, yaoosl::parsing::instance::exp_unary_state& state, size_t depth)
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
    actual->value = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives128(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_unary>& actual, yaoosl::parsing::instance::exp_unary_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_exclamation_expunary_123(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_exclamation_expunary_123(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_tilde_expunary_124(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_tilde_expunary_124(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_minus_expunary_125(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_minus_expunary_125(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_plus_expunary_126(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_plus_expunary_126(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_expnullar_127(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_expnullar_127(false, actual, state, depth + 1);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_exp_unary(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_unary> fake;
    exp_unary_state state;
    if (!alternatives128(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::exp_unary> yaoosl::parsing::instance::p_match_exp_unary(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_unary>();
    std::shared_ptr<yaoosl::parsing::instance::exp_unary> fake;
    exp_unary_state state;
    resetable resetable2(*this);
    if (alternatives128(true, fake, state, depth + 1))
    {
        resetable2.reset();
        alternatives128(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_return_expor_129(bool is_can, std::shared_ptr<yaoosl::parsing::instance::return_statement>& actual, yaoosl::parsing::instance::return_statement_state& state, size_t depth)
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
    if (!m_return_expor_129(true, fake, state, depth + 1))
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
    if (m_return_expor_129(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_return_expor_129(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_typematch_ident_130(bool is_can, std::shared_ptr<yaoosl::parsing::instance::declaration>& actual, yaoosl::parsing::instance::declaration_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_type_match(depth + 1))
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
    auto val4 = p_match_type_match(depth + 1);
    actual->type = val4;
    skip();
    auto val5 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->name = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_declaration(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::declaration> fake;
    declaration_state state;
    if (!m_typematch_ident_130(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::declaration> yaoosl::parsing::instance::p_match_declaration(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::declaration>();
    std::shared_ptr<yaoosl::parsing::instance::declaration> fake;
    declaration_state state;
    resetable resetable2(*this);
    if (m_typematch_ident_130(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_typematch_ident_130(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_returnstatement_semicolon_131(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth)
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
    auto l2 = token__semicolon(depth + 1);
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
    auto l6 = token__semicolon(depth + 1).value();
    for (;l6 != 0; l6--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expression_semicolon_132(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth)
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
    auto l2 = token__semicolon(depth + 1);
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
    auto l6 = token__semicolon(depth + 1).value();
    for (;l6 != 0; l6--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_semicolon_133(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__semicolon(depth + 1);
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
    auto l5 = token__semicolon(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives134(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_returnstatement_semicolon_131(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_returnstatement_semicolon_131(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_expression_semicolon_132(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_expression_semicolon_132(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_semicolon_133(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_semicolon_133(false, actual, state, depth + 1);
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
    if (!alternatives134(true, fake, state, depth + 1))
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
    if (alternatives134(true, fake, state, depth + 1))
    {
        resetable2.reset();
        alternatives134(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_curlybrackedopen_135(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_curlybrackedclose_136(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_controlstructure_137(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_statement_138(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
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
bool yaoosl::parsing::instance::alternatives139(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_controlstructure_137(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_controlstructure_137(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_statement_138(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_statement_138(false, actual, state, depth + 1);
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
bool yaoosl::parsing::instance::while140_141(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_curlybrackedclose_136(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives139(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_136(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives139(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives139(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_136(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_curlybrackedclose_142(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth)
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
    if (!m_curlybrackedopen_135(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!while140_141(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_curlybrackedclose_142(true, fake, state, depth + 1))
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
    if (m_curlybrackedopen_135(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_curlybrackedopen_135(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (while140_141(true, fake, state, depth + 1))
    {
        resetable3.reset();
        while140_141(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (m_curlybrackedclose_142(true, fake, state, depth + 1))
    {
        resetable4.reset();
        m_curlybrackedclose_142(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_curlybrackedopen_143(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_get_scope_set_scope_144(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
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
    auto l4 = token__set(depth + 1);
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
    auto l7 = token__get(depth + 1).value();
    for (;l7 != 0; l7--)
    {
        next();
    }
    skip();
    auto val8 = p_match_scope(depth + 1);
    actual->get = val8;
    skip();
    auto l10 = token__set(depth + 1).value();
    for (;l10 != 0; l10--)
    {
        next();
    }
    skip();
    auto val11 = p_match_scope(depth + 1);
    actual->set = val11;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_set_scope_get_scope_145(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
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
    auto l4 = token__get(depth + 1);
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
    auto l7 = token__set(depth + 1).value();
    for (;l7 != 0; l7--)
    {
        next();
    }
    skip();
    auto val8 = p_match_scope(depth + 1);
    actual->set = val8;
    skip();
    auto l10 = token__get(depth + 1).value();
    for (;l10 != 0; l10--)
    {
        next();
    }
    skip();
    auto val11 = p_match_scope(depth + 1);
    actual->get = val11;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_get_scope_146(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
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
    auto l5 = token__get(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_scope(depth + 1);
    actual->get = val6;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_set_scope_147(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
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
    auto l5 = token__set(depth + 1).value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_scope(depth + 1);
    actual->set = val6;
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives148(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_get_scope_set_scope_144(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_get_scope_set_scope_144(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_set_scope_get_scope_145(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_set_scope_get_scope_145(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_get_scope_146(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_get_scope_146(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_set_scope_147(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_set_scope_147(false, actual, state, depth + 1);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_curlybrackedclose_149(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth)
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
    if (!m_curlybrackedopen_143(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!alternatives148(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_curlybrackedclose_149(true, fake, state, depth + 1))
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
    if (m_curlybrackedopen_143(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_curlybrackedopen_143(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (alternatives148(true, fake, state, depth + 1))
    {
        resetable3.reset();
        alternatives148(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (m_curlybrackedclose_149(true, fake, state, depth + 1))
    {
        resetable4.reset();
        m_curlybrackedclose_149(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_scope_150(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure_body>& actual, yaoosl::parsing::instance::control_structure_body_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_controlstructure_151(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure_body>& actual, yaoosl::parsing::instance::control_structure_body_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_statement_152(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure_body>& actual, yaoosl::parsing::instance::control_structure_body_state& state, size_t depth)
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
bool yaoosl::parsing::instance::alternatives153(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure_body>& actual, yaoosl::parsing::instance::control_structure_body_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_scope_150(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_scope_150(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_controlstructure_151(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_controlstructure_151(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_statement_152(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_statement_152(false, actual, state, depth + 1);
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
    if (!alternatives153(true, fake, state, depth + 1))
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
    if (alternatives153(true, fake, state, depth + 1))
    {
        resetable2.reset();
        alternatives153(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_while_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_154(bool is_can, std::shared_ptr<yaoosl::parsing::instance::while_loop>& actual, yaoosl::parsing::instance::while_loop_state& state, size_t depth)
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
    if (!m_while_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_154(true, fake, state, depth + 1))
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
    if (m_while_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_154(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_while_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_154(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_if_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_155(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_body>& actual, yaoosl::parsing::instance::if_body_state& state, size_t depth)
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
    actual->body = val15;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_if_body(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::if_body> fake;
    if_body_state state;
    if (!m_if_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_155(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::if_body> yaoosl::parsing::instance::p_match_if_body(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::if_body>();
    std::shared_ptr<yaoosl::parsing::instance::if_body> fake;
    if_body_state state;
    resetable resetable2(*this);
    if (m_if_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_155(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_if_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_155(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_else_controlstructurebody_156(bool is_can, std::shared_ptr<yaoosl::parsing::instance::else_body>& actual, yaoosl::parsing::instance::else_body_state& state, size_t depth)
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
bool yaoosl::parsing::instance::p_can_else_body(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::else_body> fake;
    else_body_state state;
    if (!m_else_controlstructurebody_156(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::else_body> yaoosl::parsing::instance::p_match_else_body(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::else_body>();
    std::shared_ptr<yaoosl::parsing::instance::else_body> fake;
    else_body_state state;
    resetable resetable2(*this);
    if (m_else_controlstructurebody_156(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_else_controlstructurebody_156(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_ifbody_157(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_if_body(depth + 1))
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
    auto val2 = p_match_if_body(depth + 1);
    actual->if_ = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_elsebody_158(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_else_body(depth + 1))
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
    p_match_else_body(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_elsebody_159(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_else_body(depth + 1))
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
    auto val2 = p_match_else_body(depth + 1);
    actual->else_ = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::if160_161(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_elsebody_158(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_elsebody_159(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: else-body (XCG.Parsing.Production) }", depth);
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
            if (m_elsebody_159(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: else-body (XCG.Parsing.Production) }", depth);
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
    if (!m_ifbody_157(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!if160_161(true, fake, state, depth + 1))
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
    if (m_ifbody_157(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_ifbody_157(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (if160_161(true, fake, state, depth + 1))
    {
        resetable3.reset();
        if160_161(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_case_expvalue_colon_controlstructurebody_162(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_case>& actual, yaoosl::parsing::instance::switch_case_state& state, size_t depth)
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
    if (!m_case_expvalue_colon_controlstructurebody_162(true, fake, state, depth + 1))
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
    if (m_case_expvalue_colon_controlstructurebody_162(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_case_expvalue_colon_controlstructurebody_162(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_switch_roundbrackedopen_expression_roundbrackedclose_163(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_curlybrackedclose_164(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_switchcase_165(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth)
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
bool yaoosl::parsing::instance::if166_167(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_default_colon_controlstructurebody_168(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth)
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
    if166_167(false, actual, state, depth + 1);
    return true;
}
bool yaoosl::parsing::instance::alternatives169(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_switchcase_165(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_switchcase_165(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_default_colon_controlstructurebody_168(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_default_colon_controlstructurebody_168(false, actual, state, depth + 1);
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
bool yaoosl::parsing::instance::while170_171(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_curlybrackedclose_164(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives169(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_164(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives169(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives169(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_164(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_curlybrackedclose_172(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth)
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
    if (!m_switch_roundbrackedopen_expression_roundbrackedclose_163(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!while170_171(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_curlybrackedclose_172(true, fake, state, depth + 1))
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
    if (m_switch_roundbrackedopen_expression_roundbrackedclose_163(true, fake, state, depth + 1))
    {
        resetable3.reset();
        m_switch_roundbrackedopen_expression_roundbrackedclose_163(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (while170_171(true, fake, state, depth + 1))
    {
        resetable4.reset();
        while170_171(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable5(*this);
    if (m_curlybrackedclose_172(true, fake, state, depth + 1))
    {
        resetable5.reset();
        m_curlybrackedclose_172(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
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
    if (m_whileloop_173(true, actual, state, depth + 1))
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
    auto val4 = create_token(token__public(depth + 1).value(), tok::_PUBLIC);
    actual->tok = val4;
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
    auto val4 = create_token(token__local(depth + 1).value(), tok::_LOCAL);
    actual->tok = val4;
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
    auto val4 = create_token(token__derived(depth + 1).value(), tok::_DERIVED);
    actual->tok = val4;
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
    auto val4 = create_token(token__private(depth + 1).value(), tok::_PRIVATE);
    actual->tok = val4;
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
bool yaoosl::parsing::instance::m_attributes_183(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    p_match_attributes(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_namespace_identnavigation_184(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_curlybrackedopen_185(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_curlybrackedclose_186(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_namespace_187(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
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
    actual->namespaces.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_conversion_188(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
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
    actual->conversions.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_class_189(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
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
    actual->classes.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_method_190(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
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
    actual->methods.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives191(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_namespace_187(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_namespace_187(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_conversion_188(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_conversion_188(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_class_189(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_class_189(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_method_190(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_method_190(false, actual, state, depth + 1);
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
bool yaoosl::parsing::instance::while192_193(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_curlybrackedclose_186(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives191(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_186(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives191(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives191(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_186(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_curlybrackedclose_194(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_attributes_195(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    auto val2 = p_match_attributes(depth + 1);
    actual->att = val2;
    skip();
    if (m_namespace_identnavigation_184(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: namespace ({ Token: namespace (namespace)}), $ref: ident-navigation (XCG.Parsing.LeftRecursive) }", depth);
        return false;
    }
    if (m_curlybrackedopen_185(false, actual, state, depth + 1))
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
    while192_193(false, actual, state, depth + 1);
    if (m_curlybrackedclose_194(false, actual, state, depth + 1))
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
bool yaoosl::parsing::instance::if196_197(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_attributes_183(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_attributes_195(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
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
            if (m_attributes_195(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_namespace_(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::namespace_> fake;
    namespace__state state;
    if (!if196_197(true, fake, state, depth + 1))
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
    if (if196_197(true, fake, state, depth + 1))
    {
        resetable2.reset();
        if196_197(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_attributes_198(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    p_match_attributes(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_encapsulation_class_ident_199(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_curlybrackedopen_200(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_curlybrackedclose_201(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_indexer_202(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
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
    actual->indexers.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_operatorbinaryoverload_203(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_operator_binary_overload(depth + 1))
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
    auto val2 = p_match_operator_binary_overload(depth + 1);
    actual->operators_binary.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_operatorunaryoverload_204(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_operator_unary_overload(depth + 1))
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
    auto val2 = p_match_operator_unary_overload(depth + 1);
    actual->operators_unary.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_conversion_205(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
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
    actual->conversions.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_class_206(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
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
    actual->classes.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_constructor_207(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
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
    actual->constructors.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_destructor_208(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
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
    actual->destructors.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_copystructor_209(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
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
    actual->copystructors.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_property_210(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
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
    actual->properties.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_method_211(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
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
    actual->methods.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives212(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_indexer_202(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_indexer_202(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_operatorbinaryoverload_203(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_operatorbinaryoverload_203(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_operatorunaryoverload_204(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_operatorunaryoverload_204(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_conversion_205(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_conversion_205(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_class_206(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_class_206(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_constructor_207(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_constructor_207(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_destructor_208(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_destructor_208(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_copystructor_209(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_copystructor_209(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_property_210(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_property_210(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_method_211(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_method_211(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (!is_can)
    {
        report("Failed to match one of the following: { indexer, operator-binary-overload, operator-unary-overload, conversion, class, constructor, destructor, copystructor, property, method }", depth);
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::while213_214(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_curlybrackedclose_201(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives212(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_201(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives212(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives212(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_201(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_curlybrackedclose_215(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_attributes_216(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    auto val2 = p_match_attributes(depth + 1);
    actual->att = val2;
    skip();
    if (m_encapsulation_class_ident_199(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: encapsulation (XCG.Parsing.Production), $ref: class ({ Token: class (class)}), $ref: ident ({ Token: ident}) }", depth);
        return false;
    }
    if (m_curlybrackedopen_200(false, actual, state, depth + 1))
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
    while213_214(false, actual, state, depth + 1);
    if (m_curlybrackedclose_215(false, actual, state, depth + 1))
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
bool yaoosl::parsing::instance::if217_218(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_attributes_198(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_attributes_216(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
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
            if (m_attributes_216(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_class_(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::class_> fake;
    class__state state;
    if (!if217_218(true, fake, state, depth + 1))
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
    if (if217_218(true, fake, state, depth + 1))
    {
        resetable2.reset();
        if217_218(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_attributes_219(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item_with_default>& actual, yaoosl::parsing::instance::method_arglist_item_with_default_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    p_match_attributes(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_typematch_ident_220(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item_with_default>& actual, yaoosl::parsing::instance::method_arglist_item_with_default_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_type_match(depth + 1))
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
    auto val4 = p_match_type_match(depth + 1);
    actual->type = val4;
    skip();
    auto val5 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->name = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_equal_221(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item_with_default>& actual, yaoosl::parsing::instance::method_arglist_item_with_default_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_equal_expvalue_222(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item_with_default>& actual, yaoosl::parsing::instance::method_arglist_item_with_default_state& state, size_t depth)
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
bool yaoosl::parsing::instance::if223_224(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item_with_default>& actual, yaoosl::parsing::instance::method_arglist_item_with_default_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_equal_221(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_equal_expvalue_222(true, actual, state, depth + 1))
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
            if (m_equal_expvalue_222(false, actual, state, depth + 1))
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
bool yaoosl::parsing::instance::m_attributes_225(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item_with_default>& actual, yaoosl::parsing::instance::method_arglist_item_with_default_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    auto val2 = p_match_attributes(depth + 1);
    actual->att = val2;
    skip();
    if (m_typematch_ident_220(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: type-match (XCG.Parsing.Production), $ref: ident ({ Token: ident}) }", depth);
        return false;
    }
    if223_224(false, actual, state, depth + 1);
    return true;
}
bool yaoosl::parsing::instance::if226_227(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item_with_default>& actual, yaoosl::parsing::instance::method_arglist_item_with_default_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_attributes_219(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_attributes_225(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
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
            if (m_attributes_225(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_method_arglist_item_with_default(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::method_arglist_item_with_default> fake;
    method_arglist_item_with_default_state state;
    if (!if226_227(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::method_arglist_item_with_default> yaoosl::parsing::instance::p_match_method_arglist_item_with_default(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::method_arglist_item_with_default>();
    std::shared_ptr<yaoosl::parsing::instance::method_arglist_item_with_default> fake;
    method_arglist_item_with_default_state state;
    resetable resetable2(*this);
    if (if226_227(true, fake, state, depth + 1))
    {
        resetable2.reset();
        if226_227(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_attributes_228(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item>& actual, yaoosl::parsing::instance::method_arglist_item_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    p_match_attributes(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_typematch_ident_229(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item>& actual, yaoosl::parsing::instance::method_arglist_item_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_type_match(depth + 1))
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
    auto val4 = p_match_type_match(depth + 1);
    actual->type = val4;
    skip();
    auto val5 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->name = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_attributes_230(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item>& actual, yaoosl::parsing::instance::method_arglist_item_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    auto val2 = p_match_attributes(depth + 1);
    actual->att = val2;
    skip();
    if (m_typematch_ident_229(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: type-match (XCG.Parsing.Production), $ref: ident ({ Token: ident}) }", depth);
        return false;
    }
    return true;
}
bool yaoosl::parsing::instance::if231_232(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item>& actual, yaoosl::parsing::instance::method_arglist_item_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_attributes_228(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_attributes_230(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
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
            if (m_attributes_230(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
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
    if (!if231_232(true, fake, state, depth + 1))
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
    if (if231_232(true, fake, state, depth + 1))
    {
        resetable2.reset();
        if231_232(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_roundbrackedopen_233(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_methodarglistitemwithdefault_234(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_method_arglist_item_with_default(depth + 1))
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
    p_match_method_arglist_item_with_default(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_methodarglistitemwithdefault_235(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_method_arglist_item_with_default(depth + 1))
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
    auto val2 = p_match_method_arglist_item_with_default(depth + 1);
    actual->args.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_roundbrackedclose_236(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_comma_methodarglistitemwithdefault_237(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
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
    if (p_can_method_arglist_item_with_default(depth + 1))
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
    auto val6 = p_match_method_arglist_item_with_default(depth + 1);
    actual->args.push_back(val6);
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives238(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_comma_methodarglistitemwithdefault_237(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_comma_methodarglistitemwithdefault_237(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (!is_can)
    {
        report("Failed to match one of the following: { ,, method-arglist-item-with-default }", depth);
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::while239_240(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_roundbrackedclose_236(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives238(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_236(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives238(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives238(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_236(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_comma_241(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_comma_242(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
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
bool yaoosl::parsing::instance::if243_244(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_comma_241(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_comma_242(true, actual, state, depth + 1))
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
            if (m_comma_242(false, actual, state, depth + 1))
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
bool yaoosl::parsing::instance::if245_246(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_methodarglistitemwithdefault_234(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_methodarglistitemwithdefault_235(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: method-arglist-item-with-default (XCG.Parsing.Production) }", depth);
                return false;
            }
            while239_240(true, actual, state, depth + 1);
            if243_244(true, actual, state, depth + 1);
            return true;
        }
        return true;
    }
    else
    {
        if (cond2)
        {
            if (m_methodarglistitemwithdefault_235(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: method-arglist-item-with-default (XCG.Parsing.Production) }", depth);
                return false;
            }
            while239_240(false, actual, state, depth + 1);
            if243_244(false, actual, state, depth + 1);
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_roundbrackedclose_247(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth)
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
    if (!m_roundbrackedopen_233(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!if245_246(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_roundbrackedclose_247(true, fake, state, depth + 1))
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
    if (m_roundbrackedopen_233(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_roundbrackedopen_233(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (if245_246(true, fake, state, depth + 1))
    {
        resetable3.reset();
        if245_246(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (m_roundbrackedclose_247(true, fake, state, depth + 1))
    {
        resetable4.reset();
        m_roundbrackedclose_247(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_squarebrackedopen_248(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_methodarglistitem_249(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_squarebrackedclose_250(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_comma_methodarglistitem_251(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth)
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
bool yaoosl::parsing::instance::alternatives252(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_comma_methodarglistitem_251(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_comma_methodarglistitem_251(false, actual, state, depth + 1);
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
bool yaoosl::parsing::instance::while253_254(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_squarebrackedclose_250(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives252(true, actual, state, depth + 1) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_squarebrackedclose_250(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives252(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives252(true, actual, state, depth + 1))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_squarebrackedclose_250(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_comma_255(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_comma_256(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth)
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
bool yaoosl::parsing::instance::if257_258(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_comma_255(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_comma_256(true, actual, state, depth + 1))
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
            if (m_comma_256(false, actual, state, depth + 1))
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
bool yaoosl::parsing::instance::m_squarebrackedclose_259(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth)
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
bool yaoosl::parsing::instance::p_can_method_arglist_indexer(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer> fake;
    method_arglist_indexer_state state;
    if (!m_squarebrackedopen_248(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_methodarglistitem_249(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!while253_254(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!if257_258(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_squarebrackedclose_259(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer> yaoosl::parsing::instance::p_match_method_arglist_indexer(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::method_arglist_indexer>();
    std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer> fake;
    method_arglist_indexer_state state;
    resetable resetable2(*this);
    if (m_squarebrackedopen_248(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_squarebrackedopen_248(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (m_methodarglistitem_249(true, fake, state, depth + 1))
    {
        resetable3.reset();
        m_methodarglistitem_249(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (while253_254(true, fake, state, depth + 1))
    {
        resetable4.reset();
        while253_254(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable5(*this);
    if (if257_258(true, fake, state, depth + 1))
    {
        resetable5.reset();
        if257_258(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable6(*this);
    if (m_squarebrackedclose_259(true, fake, state, depth + 1))
    {
        resetable6.reset();
        m_squarebrackedclose_259(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_ident_260(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_ident>& actual, yaoosl::parsing::instance::method_ident_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_templatedefinition_261(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_ident>& actual, yaoosl::parsing::instance::method_ident_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_templatedefinition_262(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_ident>& actual, yaoosl::parsing::instance::method_ident_state& state, size_t depth)
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
bool yaoosl::parsing::instance::if263_264(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_ident>& actual, yaoosl::parsing::instance::method_ident_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_templatedefinition_261(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_templatedefinition_262(true, actual, state, depth + 1))
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
            if (m_templatedefinition_262(false, actual, state, depth + 1))
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
    if (!m_ident_260(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!if263_264(true, fake, state, depth + 1))
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
    if (m_ident_260(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_ident_260(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (if263_264(true, fake, state, depth + 1))
    {
        resetable3.reset();
        if263_264(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_attributes_265(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    p_match_attributes(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_encapsulation_266(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_unbound_267(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_unbound_268(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth)
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
bool yaoosl::parsing::instance::if269_270(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_unbound_267(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_unbound_268(true, actual, state, depth + 1))
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
            if (m_unbound_268(false, actual, state, depth + 1))
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
bool yaoosl::parsing::instance::m_typematch_methodident_methodarglist_scope_271(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_type_match(depth + 1))
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
    auto val2 = p_match_type_match(depth + 1);
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
bool yaoosl::parsing::instance::m_attributes_272(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    auto val2 = p_match_attributes(depth + 1);
    actual->att = val2;
    skip();
    if (m_encapsulation_266(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: encapsulation (XCG.Parsing.Production) }", depth);
        return false;
    }
    if269_270(false, actual, state, depth + 1);
    if (m_typematch_methodident_methodarglist_scope_271(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: type-match (XCG.Parsing.Production), $ref: method-ident (XCG.Parsing.Production), $ref: method-arglist (XCG.Parsing.Production), $ref: scope (XCG.Parsing.Production) }", depth);
        return false;
    }
    return true;
}
bool yaoosl::parsing::instance::if273_274(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_attributes_265(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_attributes_272(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
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
            if (m_attributes_272(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_method(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::method> fake;
    method_state state;
    if (!if273_274(true, fake, state, depth + 1))
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
    if (if273_274(true, fake, state, depth + 1))
    {
        resetable2.reset();
        if273_274(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_attributes_275(bool is_can, std::shared_ptr<yaoosl::parsing::instance::constructor>& actual, yaoosl::parsing::instance::constructor_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    p_match_attributes(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_encapsulation_methodident_methodarglist_scope_276(bool is_can, std::shared_ptr<yaoosl::parsing::instance::constructor>& actual, yaoosl::parsing::instance::constructor_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_attributes_277(bool is_can, std::shared_ptr<yaoosl::parsing::instance::constructor>& actual, yaoosl::parsing::instance::constructor_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    auto val2 = p_match_attributes(depth + 1);
    actual->att = val2;
    skip();
    if (m_encapsulation_methodident_methodarglist_scope_276(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: encapsulation (XCG.Parsing.Production), $ref: method-ident (XCG.Parsing.Production), $ref: method-arglist (XCG.Parsing.Production), $ref: scope (XCG.Parsing.Production) }", depth);
        return false;
    }
    return true;
}
bool yaoosl::parsing::instance::if278_279(bool is_can, std::shared_ptr<yaoosl::parsing::instance::constructor>& actual, yaoosl::parsing::instance::constructor_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_attributes_275(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_attributes_277(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
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
            if (m_attributes_277(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_constructor(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::constructor> fake;
    constructor_state state;
    if (!if278_279(true, fake, state, depth + 1))
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
    if (if278_279(true, fake, state, depth + 1))
    {
        resetable2.reset();
        if278_279(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_attributes_280(bool is_can, std::shared_ptr<yaoosl::parsing::instance::destructor>& actual, yaoosl::parsing::instance::destructor_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    p_match_attributes(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_encapsulation_tilde_methodident_methodarglist_scope_281(bool is_can, std::shared_ptr<yaoosl::parsing::instance::destructor>& actual, yaoosl::parsing::instance::destructor_state& state, size_t depth)
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
    auto l6 = token__tilde(depth + 1).value();
    for (;l6 != 0; l6--)
    {
        next();
    }
    skip();
    auto val7 = p_match_method_ident(depth + 1);
    actual->ident = val7;
    skip();
    auto val8 = p_match_method_arglist(depth + 1);
    actual->arglist = val8;
    skip();
    auto val9 = p_match_scope(depth + 1);
    actual->body = val9;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_attributes_282(bool is_can, std::shared_ptr<yaoosl::parsing::instance::destructor>& actual, yaoosl::parsing::instance::destructor_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    auto val2 = p_match_attributes(depth + 1);
    actual->att = val2;
    skip();
    if (m_encapsulation_tilde_methodident_methodarglist_scope_281(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: encapsulation (XCG.Parsing.Production), $ref: ~ ({ Token: ~ (~)}), $ref: method-ident (XCG.Parsing.Production), $ref: method-arglist (XCG.Parsing.Production), $ref: scope (XCG.Parsing.Production) }", depth);
        return false;
    }
    return true;
}
bool yaoosl::parsing::instance::if283_284(bool is_can, std::shared_ptr<yaoosl::parsing::instance::destructor>& actual, yaoosl::parsing::instance::destructor_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_attributes_280(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_attributes_282(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
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
            if (m_attributes_282(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_destructor(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::destructor> fake;
    destructor_state state;
    if (!if283_284(true, fake, state, depth + 1))
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
    if (if283_284(true, fake, state, depth + 1))
    {
        resetable2.reset();
        if283_284(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_attributes_285(bool is_can, std::shared_ptr<yaoosl::parsing::instance::copystructor>& actual, yaoosl::parsing::instance::copystructor_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    p_match_attributes(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_encapsulation_plus_methodident_methodarglist_286(bool is_can, std::shared_ptr<yaoosl::parsing::instance::copystructor>& actual, yaoosl::parsing::instance::copystructor_state& state, size_t depth)
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
    auto l6 = token_plus(depth + 1).value();
    for (;l6 != 0; l6--)
    {
        next();
    }
    skip();
    auto val7 = p_match_method_ident(depth + 1);
    actual->ident = val7;
    skip();
    auto val8 = p_match_method_arglist(depth + 1);
    actual->arglist = val8;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_scope_287(bool is_can, std::shared_ptr<yaoosl::parsing::instance::copystructor>& actual, yaoosl::parsing::instance::copystructor_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_equal_delete_288(bool is_can, std::shared_ptr<yaoosl::parsing::instance::copystructor>& actual, yaoosl::parsing::instance::copystructor_state& state, size_t depth)
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
bool yaoosl::parsing::instance::alternatives289(bool is_can, std::shared_ptr<yaoosl::parsing::instance::copystructor>& actual, yaoosl::parsing::instance::copystructor_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_scope_287(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_scope_287(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_equal_delete_288(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_equal_delete_288(false, actual, state, depth + 1);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_attributes_290(bool is_can, std::shared_ptr<yaoosl::parsing::instance::copystructor>& actual, yaoosl::parsing::instance::copystructor_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    auto val2 = p_match_attributes(depth + 1);
    actual->att = val2;
    skip();
    if (m_encapsulation_plus_methodident_methodarglist_286(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: encapsulation (XCG.Parsing.Production), $ref: + ({ Token: + (+)}), $ref: method-ident (XCG.Parsing.Production), $ref: method-arglist (XCG.Parsing.Production) }", depth);
        return false;
    }
    alternatives289(false, actual, state, depth + 1);
    return true;
}
bool yaoosl::parsing::instance::if291_292(bool is_can, std::shared_ptr<yaoosl::parsing::instance::copystructor>& actual, yaoosl::parsing::instance::copystructor_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_attributes_285(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_attributes_290(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
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
            if (m_attributes_290(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_copystructor(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::copystructor> fake;
    copystructor_state state;
    if (!if291_292(true, fake, state, depth + 1))
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
    if (if291_292(true, fake, state, depth + 1))
    {
        resetable2.reset();
        if291_292(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_attributes_293(bool is_can, std::shared_ptr<yaoosl::parsing::instance::conversion>& actual, yaoosl::parsing::instance::conversion_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    p_match_attributes(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_encapsulation_unbound_conversion_typematch_294(bool is_can, std::shared_ptr<yaoosl::parsing::instance::conversion>& actual, yaoosl::parsing::instance::conversion_state& state, size_t depth)
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
    auto l4 = token__conversion(depth + 1);
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
    if (p_can_type_match(depth + 1))
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
    auto val6 = p_match_encapsulation(depth + 1);
    actual->encaps = val6;
    skip();
    auto l8 = token__unbound(depth + 1).value();
    for (;l8 != 0; l8--)
    {
        next();
    }
    skip();
    auto l10 = token__conversion(depth + 1).value();
    for (;l10 != 0; l10--)
    {
        next();
    }
    skip();
    auto val11 = p_match_type_match(depth + 1);
    actual->target_type = val11;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_roundbrackedopen_typematch_ident_roundbrackedclose_295(bool is_can, std::shared_ptr<yaoosl::parsing::instance::conversion>& actual, yaoosl::parsing::instance::conversion_state& state, size_t depth)
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
    if (p_can_type_match(depth + 1))
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
    auto l9 = token__round_bracked_open(depth + 1).value();
    for (;l9 != 0; l9--)
    {
        next();
    }
    skip();
    auto val10 = p_match_type_match(depth + 1);
    actual->source_type = val10;
    skip();
    auto val11 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->name = val11;
    skip();
    auto l13 = token__round_bracked_close(depth + 1).value();
    for (;l13 != 0; l13--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_scope_296(bool is_can, std::shared_ptr<yaoosl::parsing::instance::conversion>& actual, yaoosl::parsing::instance::conversion_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_attributes_297(bool is_can, std::shared_ptr<yaoosl::parsing::instance::conversion>& actual, yaoosl::parsing::instance::conversion_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    auto val2 = p_match_attributes(depth + 1);
    actual->att = val2;
    skip();
    if (m_encapsulation_unbound_conversion_typematch_294(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: encapsulation (XCG.Parsing.Production), $ref: unbound ({ Token: unbound (unbound)}), $ref: conversion ({ Token: conversion (conversion)}), $ref: type-match (XCG.Parsing.Production) }", depth);
        return false;
    }
    if (m_roundbrackedopen_typematch_ident_roundbrackedclose_295(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: ( ({ Token: ( (()}), $ref: type-match (XCG.Parsing.Production), $ref: ident ({ Token: ident}), $ref: ) ({ Token: ) ())}) }", depth);
        return false;
    }
    if (m_scope_296(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: scope (XCG.Parsing.Production) }", depth);
        return false;
    }
    return true;
}
bool yaoosl::parsing::instance::if298_299(bool is_can, std::shared_ptr<yaoosl::parsing::instance::conversion>& actual, yaoosl::parsing::instance::conversion_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_attributes_293(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_attributes_297(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
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
            if (m_attributes_297(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_conversion(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::conversion> fake;
    conversion_state state;
    if (!if298_299(true, fake, state, depth + 1))
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
    if (if298_299(true, fake, state, depth + 1))
    {
        resetable2.reset();
        if298_299(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_attributes_300(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    p_match_attributes(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_encapsulation_typematch_301(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth)
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
    if (p_can_type_match(depth + 1))
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
    auto val3 = p_match_type_match(depth + 1);
    actual->target_type = val3;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_templatedefinition_302(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_templatedefinition_303(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth)
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
bool yaoosl::parsing::instance::if304_305(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_templatedefinition_302(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_templatedefinition_303(true, actual, state, depth + 1))
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
            if (m_templatedefinition_303(false, actual, state, depth + 1))
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
bool yaoosl::parsing::instance::m_methodarglistindexer_scopegetset_306(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_method_arglist_indexer(depth + 1))
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
    auto val2 = p_match_method_arglist_indexer(depth + 1);
    actual->arglist = val2;
    skip();
    auto val3 = p_match_scope_getset(depth + 1);
    actual->body = val3;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_attributes_307(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    auto val2 = p_match_attributes(depth + 1);
    actual->att = val2;
    skip();
    if (m_encapsulation_typematch_301(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: encapsulation (XCG.Parsing.Production), $ref: type-match (XCG.Parsing.Production) }", depth);
        return false;
    }
    if304_305(false, actual, state, depth + 1);
    if (m_methodarglistindexer_scopegetset_306(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: method-arglist-indexer (XCG.Parsing.Production), $ref: scope-getset (XCG.Parsing.Production) }", depth);
        return false;
    }
    return true;
}
bool yaoosl::parsing::instance::if308_309(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_attributes_300(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_attributes_307(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
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
            if (m_attributes_307(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_indexer(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::indexer> fake;
    indexer_state state;
    if (!if308_309(true, fake, state, depth + 1))
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
    if (if308_309(true, fake, state, depth + 1))
    {
        resetable2.reset();
        if308_309(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_attributes_310(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    p_match_attributes(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_encapsulation_unbound_typematch_operator_311(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
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
    if (p_can_type_match(depth + 1))
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
    auto l4 = token__operator(depth + 1);
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
    auto l8 = token__unbound(depth + 1).value();
    for (;l8 != 0; l8--)
    {
        next();
    }
    skip();
    auto val9 = p_match_type_match(depth + 1);
    actual->target_type = val9;
    skip();
    auto l11 = token__operator(depth + 1).value();
    for (;l11 != 0; l11--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_templatedefinition_312(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_templatedefinition_313(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
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
bool yaoosl::parsing::instance::if314_315(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_templatedefinition_312(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_templatedefinition_313(true, actual, state, depth + 1))
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
            if (m_templatedefinition_313(false, actual, state, depth + 1))
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
bool yaoosl::parsing::instance::m_roundbrackedopen_methodarglistitem_roundbrackedclose_316(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
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
    auto val8 = p_match_method_arglist_item(depth + 1);
    actual->left = val8;
    skip();
    auto l10 = token__round_bracked_close(depth + 1).value();
    for (;l10 != 0; l10--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_plus_317(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
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
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_plus(depth + 1).value(), tok::PLUS);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_minus_318(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
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
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_minus(depth + 1).value(), tok::MINUS);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_star_319(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
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
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_star(depth + 1).value(), tok::STAR);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_slash_320(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
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
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_slash(depth + 1).value(), tok::SLASH);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_lessthenlessthenlessthen_321(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__less_then_less_then_less_then(depth + 1);
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
    auto val4 = create_token(token__less_then_less_then_less_then(depth + 1).value(), tok::_LESS_THEN_LESS_THEN_LESS_THEN);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_lessthenlessthen_322(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__less_then_less_then(depth + 1);
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
    auto val4 = create_token(token__less_then_less_then(depth + 1).value(), tok::_LESS_THEN_LESS_THEN);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_lessthenequal_323(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
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
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token__less_then_equal(depth + 1).value(), tok::_LESS_THEN_EQUAL);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_lessthen_324(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
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
    auto val4 = create_token(token__less_then(depth + 1).value(), tok::_LESS_THEN);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_greaterthengreaterthengreaterthen_325(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__greater_then_greater_then_greater_then(depth + 1);
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
    auto val4 = create_token(token__greater_then_greater_then_greater_then(depth + 1).value(), tok::_GREATER_THEN_GREATER_THEN_GREATER_THEN);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_greaterthengreaterthen_326(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__greater_then_greater_then(depth + 1);
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
    auto val4 = create_token(token__greater_then_greater_then(depth + 1).value(), tok::_GREATER_THEN_GREATER_THEN);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_greaterthenequal_327(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
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
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token__greater_then_equal(depth + 1).value(), tok::_GREATER_THEN_EQUAL);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_greaterthen_328(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
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
    auto val4 = create_token(token__greater_then(depth + 1).value(), tok::_GREATER_THEN);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_verticalbarverticalbar_329(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__vertical_bar_vertical_bar(depth + 1);
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
    auto val4 = create_token(token__vertical_bar_vertical_bar(depth + 1).value(), tok::_VERTICAL_BAR_VERTICAL_BAR);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_verticalbar_330(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__vertical_bar(depth + 1);
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
    auto val4 = create_token(token__vertical_bar(depth + 1).value(), tok::_VERTICAL_BAR);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_ampersandampersand_331(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__ampersand_ampersand(depth + 1);
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
    auto val4 = create_token(token__ampersand_ampersand(depth + 1).value(), tok::_AMPERSAND_AMPERSAND);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_ampersand_332(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__ampersand(depth + 1);
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
    auto val4 = create_token(token__ampersand(depth + 1).value(), tok::_AMPERSAND);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives333(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_plus_317(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_plus_317(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_minus_318(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_minus_318(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_star_319(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_star_319(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_slash_320(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_slash_320(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_lessthenlessthenlessthen_321(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_lessthenlessthenlessthen_321(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_lessthenlessthen_322(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_lessthenlessthen_322(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_lessthenequal_323(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_lessthenequal_323(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_lessthen_324(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_lessthen_324(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_greaterthengreaterthengreaterthen_325(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_greaterthengreaterthengreaterthen_325(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_greaterthengreaterthen_326(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_greaterthengreaterthen_326(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_greaterthenequal_327(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_greaterthenequal_327(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_greaterthen_328(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_greaterthen_328(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_verticalbarverticalbar_329(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_verticalbarverticalbar_329(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_verticalbar_330(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_verticalbar_330(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_ampersandampersand_331(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_ampersandampersand_331(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_ampersand_332(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_ampersand_332(false, actual, state, depth + 1);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_roundbrackedopen_methodarglistitem_roundbrackedclose_334(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
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
    auto val8 = p_match_method_arglist_item(depth + 1);
    actual->right = val8;
    skip();
    auto l10 = token__round_bracked_close(depth + 1).value();
    for (;l10 != 0; l10--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_scope_335(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_attributes_336(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    auto val2 = p_match_attributes(depth + 1);
    actual->att = val2;
    skip();
    if (m_encapsulation_unbound_typematch_operator_311(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: encapsulation (XCG.Parsing.Production), $ref: unbound ({ Token: unbound (unbound)}), $ref: type-match (XCG.Parsing.Production), $ref: operator ({ Token: operator (operator)}) }", depth);
        return false;
    }
    if314_315(false, actual, state, depth + 1);
    if (m_roundbrackedopen_methodarglistitem_roundbrackedclose_316(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: ( ({ Token: ( (()}), $ref: method-arglist-item (XCG.Parsing.Production), $ref: ) ({ Token: ) ())}) }", depth);
        return false;
    }
    alternatives333(false, actual, state, depth + 1);
    if (m_roundbrackedopen_methodarglistitem_roundbrackedclose_334(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: ( ({ Token: ( (()}), $ref: method-arglist-item (XCG.Parsing.Production), $ref: ) ({ Token: ) ())}) }", depth);
        return false;
    }
    if (m_scope_335(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: scope (XCG.Parsing.Production) }", depth);
        return false;
    }
    return true;
}
bool yaoosl::parsing::instance::if337_338(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_attributes_310(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_attributes_336(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
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
            if (m_attributes_336(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_operator_binary_overload(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload> fake;
    operator_binary_overload_state state;
    if (!if337_338(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload> yaoosl::parsing::instance::p_match_operator_binary_overload(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::operator_binary_overload>();
    std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload> fake;
    operator_binary_overload_state state;
    resetable resetable2(*this);
    if (if337_338(true, fake, state, depth + 1))
    {
        resetable2.reset();
        if337_338(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_attributes_339(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    p_match_attributes(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_encapsulation_unbound_typematch_operator_340(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth)
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
    if (p_can_type_match(depth + 1))
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
    auto l4 = token__operator(depth + 1);
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
    auto l8 = token__unbound(depth + 1).value();
    for (;l8 != 0; l8--)
    {
        next();
    }
    skip();
    auto val9 = p_match_type_match(depth + 1);
    actual->target_type = val9;
    skip();
    auto l11 = token__operator(depth + 1).value();
    for (;l11 != 0; l11--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_templatedefinition_341(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_templatedefinition_342(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth)
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
bool yaoosl::parsing::instance::if343_344(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_templatedefinition_341(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_templatedefinition_342(true, actual, state, depth + 1))
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
            if (m_templatedefinition_342(false, actual, state, depth + 1))
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
bool yaoosl::parsing::instance::m_plus_345(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth)
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
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_plus(depth + 1).value(), tok::PLUS);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_minus_346(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth)
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
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_minus(depth + 1).value(), tok::MINUS);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_exclamation_347(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__exclamation(depth + 1);
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
    auto val4 = create_token(token__exclamation(depth + 1).value(), tok::_EXCLAMATION);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_tilde_348(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
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
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token__tilde(depth + 1).value(), tok::_TILDE);
    actual->operator_ = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives349(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_plus_345(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_plus_345(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_minus_346(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_minus_346(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_exclamation_347(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_exclamation_347(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_tilde_348(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_tilde_348(false, actual, state, depth + 1);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_roundbrackedopen_methodarglistitem_roundbrackedclose_350(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth)
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
    auto val8 = p_match_method_arglist_item(depth + 1);
    actual->right = val8;
    skip();
    auto l10 = token__round_bracked_close(depth + 1).value();
    for (;l10 != 0; l10--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_scope_351(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_attributes_352(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    auto val2 = p_match_attributes(depth + 1);
    actual->att = val2;
    skip();
    if (m_encapsulation_unbound_typematch_operator_340(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: encapsulation (XCG.Parsing.Production), $ref: unbound ({ Token: unbound (unbound)}), $ref: type-match (XCG.Parsing.Production), $ref: operator ({ Token: operator (operator)}) }", depth);
        return false;
    }
    if343_344(false, actual, state, depth + 1);
    alternatives349(false, actual, state, depth + 1);
    if (m_roundbrackedopen_methodarglistitem_roundbrackedclose_350(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: ( ({ Token: ( (()}), $ref: method-arglist-item (XCG.Parsing.Production), $ref: ) ({ Token: ) ())}) }", depth);
        return false;
    }
    if (m_scope_351(false, actual, state, depth + 1))
    {
        skip();
    }
    else if (is_can)
    {
        return false;
    }
    else
    {
        report("Failed to match { $ref: scope (XCG.Parsing.Production) }", depth);
        return false;
    }
    return true;
}
bool yaoosl::parsing::instance::if353_354(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_attributes_339(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_attributes_352(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
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
            if (m_attributes_352(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_operator_unary_overload(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload> fake;
    operator_unary_overload_state state;
    if (!if353_354(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload> yaoosl::parsing::instance::p_match_operator_unary_overload(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::operator_unary_overload>();
    std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload> fake;
    operator_unary_overload_state state;
    resetable resetable2(*this);
    if (if353_354(true, fake, state, depth + 1))
    {
        resetable2.reset();
        if353_354(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_attributes_355(bool is_can, std::shared_ptr<yaoosl::parsing::instance::property>& actual, yaoosl::parsing::instance::property_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    p_match_attributes(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_encapsulation_typematch_ident_semicolon_356(bool is_can, std::shared_ptr<yaoosl::parsing::instance::property>& actual, yaoosl::parsing::instance::property_state& state, size_t depth)
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
    if (p_can_type_match(depth + 1))
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
    auto l4 = token__semicolon(depth + 1);
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
    auto val7 = p_match_type_match(depth + 1);
    actual->target_type = val7;
    skip();
    auto val8 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->name = val8;
    skip();
    auto l10 = token__semicolon(depth + 1).value();
    for (;l10 != 0; l10--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_encapsulation_typematch_ident_scopegetset_357(bool is_can, std::shared_ptr<yaoosl::parsing::instance::property>& actual, yaoosl::parsing::instance::property_state& state, size_t depth)
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
    if (p_can_type_match(depth + 1))
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
    auto val5 = p_match_type_match(depth + 1);
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
bool yaoosl::parsing::instance::alternatives358(bool is_can, std::shared_ptr<yaoosl::parsing::instance::property>& actual, yaoosl::parsing::instance::property_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_encapsulation_typematch_ident_semicolon_356(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_encapsulation_typematch_ident_semicolon_356(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_encapsulation_typematch_ident_scopegetset_357(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_encapsulation_typematch_ident_scopegetset_357(false, actual, state, depth + 1);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_attributes_359(bool is_can, std::shared_ptr<yaoosl::parsing::instance::property>& actual, yaoosl::parsing::instance::property_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attributes(depth + 1))
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
    auto val2 = p_match_attributes(depth + 1);
    actual->att = val2;
    skip();
    alternatives358(false, actual, state, depth + 1);
    return true;
}
bool yaoosl::parsing::instance::if360_361(bool is_can, std::shared_ptr<yaoosl::parsing::instance::property>& actual, yaoosl::parsing::instance::property_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_attributes_355(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_attributes_359(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
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
            if (m_attributes_359(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attributes (XCG.Parsing.Production) }", depth);
                return false;
            }
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_property(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::property> fake;
    property_state state;
    if (!if360_361(true, fake, state, depth + 1))
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
    if (if360_361(true, fake, state, depth + 1))
    {
        resetable2.reset();
        if360_361(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expor_362(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_arg_item_a>& actual, yaoosl::parsing::instance::attribute_arg_item_a_state& state, size_t depth)
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
bool yaoosl::parsing::instance::p_can_attribute_arg_item_a(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::attribute_arg_item_a> fake;
    attribute_arg_item_a_state state;
    if (!m_expor_362(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::attribute_arg_item_a> yaoosl::parsing::instance::p_match_attribute_arg_item_a(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::attribute_arg_item_a>();
    std::shared_ptr<yaoosl::parsing::instance::attribute_arg_item_a> fake;
    attribute_arg_item_a_state state;
    resetable resetable2(*this);
    if (m_expor_362(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_expor_362(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_ident_colon_expor_363(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_arg_item_b>& actual, yaoosl::parsing::instance::attribute_arg_item_b_state& state, size_t depth)
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
    auto val6 = create_token(token_ident(depth + 1).value(), tok::IDENT);
    actual->name = val6;
    skip();
    auto l8 = token__colon(depth + 1).value();
    for (;l8 != 0; l8--)
    {
        next();
    }
    skip();
    auto val9 = lr_match_exp_or(depth + 1);
    actual->value = val9;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_attribute_arg_item_b(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::attribute_arg_item_b> fake;
    attribute_arg_item_b_state state;
    if (!m_ident_colon_expor_363(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::attribute_arg_item_b> yaoosl::parsing::instance::p_match_attribute_arg_item_b(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::attribute_arg_item_b>();
    std::shared_ptr<yaoosl::parsing::instance::attribute_arg_item_b> fake;
    attribute_arg_item_b_state state;
    resetable resetable2(*this);
    if (m_ident_colon_expor_363(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_ident_colon_expor_363(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_attributeargitema_364(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_args>& actual, yaoosl::parsing::instance::attribute_args_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attribute_arg_item_a(depth + 1))
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
    p_match_attribute_arg_item_a(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_attributeargitema_365(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_args>& actual, yaoosl::parsing::instance::attribute_args_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attribute_arg_item_a(depth + 1))
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
    auto val2 = p_match_attribute_arg_item_a(depth + 1);
    actual->args.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_attributeargitema_366(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_args>& actual, yaoosl::parsing::instance::attribute_args_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attribute_arg_item_a(depth + 1))
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
    p_match_attribute_arg_item_a(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_comma_attributeargitema_367(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_args>& actual, yaoosl::parsing::instance::attribute_args_state& state, size_t depth)
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
    if (p_can_attribute_arg_item_a(depth + 1))
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
    auto val6 = p_match_attribute_arg_item_a(depth + 1);
    actual->args.push_back(val6);
    skip();
    return true;
}
bool yaoosl::parsing::instance::while368_369(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_args>& actual, yaoosl::parsing::instance::attribute_args_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_attributeargitema_366(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (cond3 && current() != '\0')
        {
            if (m_comma_attributeargitema_367(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: , ({ Token: , (,)}), $ref: attribute-arg-item-a (XCG.Parsing.Production) }", depth);
                return false;
            }
            resetable resetable2(*this);
            cond3 = m_attributeargitema_366(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (cond3 && current() != '\0')
        {
            if (m_comma_attributeargitema_367(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: , ({ Token: , (,)}), $ref: attribute-arg-item-a (XCG.Parsing.Production) }", depth);
                return false;
            }
            resetable resetable2(*this);
            cond3 = m_attributeargitema_366(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_comma_370(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_args>& actual, yaoosl::parsing::instance::attribute_args_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_comma_371(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_args>& actual, yaoosl::parsing::instance::attribute_args_state& state, size_t depth)
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
bool yaoosl::parsing::instance::if372_373(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_args>& actual, yaoosl::parsing::instance::attribute_args_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_comma_370(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_comma_371(true, actual, state, depth + 1))
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
            if (m_comma_371(false, actual, state, depth + 1))
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
bool yaoosl::parsing::instance::if374_375(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_args>& actual, yaoosl::parsing::instance::attribute_args_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_attributeargitema_364(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_attributeargitema_365(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attribute-arg-item-a (XCG.Parsing.Production) }", depth);
                return false;
            }
            while368_369(true, actual, state, depth + 1);
            if372_373(true, actual, state, depth + 1);
            return true;
        }
        return true;
    }
    else
    {
        if (cond2)
        {
            if (m_attributeargitema_365(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attribute-arg-item-a (XCG.Parsing.Production) }", depth);
                return false;
            }
            while368_369(false, actual, state, depth + 1);
            if372_373(false, actual, state, depth + 1);
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_attributeargitemb_376(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_args>& actual, yaoosl::parsing::instance::attribute_args_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attribute_arg_item_b(depth + 1))
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
    p_match_attribute_arg_item_b(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_attributeargitemb_377(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_args>& actual, yaoosl::parsing::instance::attribute_args_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attribute_arg_item_b(depth + 1))
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
    auto val2 = p_match_attribute_arg_item_b(depth + 1);
    actual->args.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_attributeargitemb_378(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_args>& actual, yaoosl::parsing::instance::attribute_args_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attribute_arg_item_b(depth + 1))
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
    p_match_attribute_arg_item_b(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_comma_attributeargitemb_379(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_args>& actual, yaoosl::parsing::instance::attribute_args_state& state, size_t depth)
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
    if (p_can_attribute_arg_item_b(depth + 1))
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
    auto val6 = p_match_attribute_arg_item_b(depth + 1);
    actual->args.push_back(val6);
    skip();
    return true;
}
bool yaoosl::parsing::instance::while380_381(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_args>& actual, yaoosl::parsing::instance::attribute_args_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_attributeargitemb_378(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (cond3 && current() != '\0')
        {
            if (m_comma_attributeargitemb_379(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: , ({ Token: , (,)}), $ref: attribute-arg-item-b (XCG.Parsing.Production) }", depth);
                return false;
            }
            resetable resetable2(*this);
            cond3 = m_attributeargitemb_378(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (cond3 && current() != '\0')
        {
            if (m_comma_attributeargitemb_379(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: , ({ Token: , (,)}), $ref: attribute-arg-item-b (XCG.Parsing.Production) }", depth);
                return false;
            }
            resetable resetable2(*this);
            cond3 = m_attributeargitemb_378(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_comma_382(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_args>& actual, yaoosl::parsing::instance::attribute_args_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_comma_383(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_args>& actual, yaoosl::parsing::instance::attribute_args_state& state, size_t depth)
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
bool yaoosl::parsing::instance::if384_385(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_args>& actual, yaoosl::parsing::instance::attribute_args_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_comma_382(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_comma_383(true, actual, state, depth + 1))
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
            if (m_comma_383(false, actual, state, depth + 1))
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
bool yaoosl::parsing::instance::if386_387(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_args>& actual, yaoosl::parsing::instance::attribute_args_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_attributeargitemb_376(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_attributeargitemb_377(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attribute-arg-item-b (XCG.Parsing.Production) }", depth);
                return false;
            }
            while380_381(true, actual, state, depth + 1);
            if384_385(true, actual, state, depth + 1);
            return true;
        }
        return true;
    }
    else
    {
        if (cond2)
        {
            if (m_attributeargitemb_377(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attribute-arg-item-b (XCG.Parsing.Production) }", depth);
                return false;
            }
            while380_381(false, actual, state, depth + 1);
            if384_385(false, actual, state, depth + 1);
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_attribute_args(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::attribute_args> fake;
    attribute_args_state state;
    if (!if374_375(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!if386_387(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::attribute_args> yaoosl::parsing::instance::p_match_attribute_args(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::attribute_args>();
    std::shared_ptr<yaoosl::parsing::instance::attribute_args> fake;
    attribute_args_state state;
    resetable resetable2(*this);
    if (if374_375(true, fake, state, depth + 1))
    {
        resetable2.reset();
        if374_375(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (if386_387(true, fake, state, depth + 1))
    {
        resetable3.reset();
        if386_387(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_typematch_388(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_item>& actual, yaoosl::parsing::instance::attribute_item_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_type_match(depth + 1))
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
    auto val2 = p_match_type_match(depth + 1);
    actual->target_type = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_typematch_roundbrackedopen_roundbrackedclose_389(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_item>& actual, yaoosl::parsing::instance::attribute_item_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_type_match(depth + 1))
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
    auto val6 = p_match_type_match(depth + 1);
    actual->target_type = val6;
    skip();
    auto l8 = token__round_bracked_open(depth + 1).value();
    for (;l8 != 0; l8--)
    {
        next();
    }
    skip();
    auto l10 = token__round_bracked_close(depth + 1).value();
    for (;l10 != 0; l10--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_typematch_roundbrackedopen_attributeargs_roundbrackedclose_390(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_item>& actual, yaoosl::parsing::instance::attribute_item_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_type_match(depth + 1))
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
    if (p_can_attribute_args(depth + 1))
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
    auto val6 = p_match_type_match(depth + 1);
    actual->target_type = val6;
    skip();
    auto l8 = token__round_bracked_open(depth + 1).value();
    for (;l8 != 0; l8--)
    {
        next();
    }
    skip();
    auto val9 = p_match_attribute_args(depth + 1);
    actual->args = val9;
    skip();
    auto l11 = token__round_bracked_close(depth + 1).value();
    for (;l11 != 0; l11--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives391(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute_item>& actual, yaoosl::parsing::instance::attribute_item_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_typematch_388(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_typematch_388(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_typematch_roundbrackedopen_roundbrackedclose_389(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_typematch_roundbrackedopen_roundbrackedclose_389(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_typematch_roundbrackedopen_attributeargs_roundbrackedclose_390(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_typematch_roundbrackedopen_attributeargs_roundbrackedclose_390(false, actual, state, depth + 1);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_attribute_item(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::attribute_item> fake;
    attribute_item_state state;
    if (!alternatives391(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::attribute_item> yaoosl::parsing::instance::p_match_attribute_item(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::attribute_item>();
    std::shared_ptr<yaoosl::parsing::instance::attribute_item> fake;
    attribute_item_state state;
    resetable resetable2(*this);
    if (alternatives391(true, fake, state, depth + 1))
    {
        resetable2.reset();
        alternatives391(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_squarebrackedopen_392(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute>& actual, yaoosl::parsing::instance::attribute_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_attributeitem_393(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute>& actual, yaoosl::parsing::instance::attribute_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attribute_item(depth + 1))
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
    p_match_attribute_item(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_attributeitem_394(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute>& actual, yaoosl::parsing::instance::attribute_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attribute_item(depth + 1))
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
    auto val2 = p_match_attribute_item(depth + 1);
    actual->items.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_attributeitem_395(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute>& actual, yaoosl::parsing::instance::attribute_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attribute_item(depth + 1))
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
    p_match_attribute_item(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_comma_attributeitem_396(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute>& actual, yaoosl::parsing::instance::attribute_state& state, size_t depth)
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
    if (p_can_attribute_item(depth + 1))
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
    auto val6 = p_match_attribute_item(depth + 1);
    actual->items.push_back(val6);
    skip();
    return true;
}
bool yaoosl::parsing::instance::while397_398(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute>& actual, yaoosl::parsing::instance::attribute_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_attributeitem_395(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (cond3 && current() != '\0')
        {
            if (m_comma_attributeitem_396(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: , ({ Token: , (,)}), $ref: attribute-item (XCG.Parsing.Production) }", depth);
                return false;
            }
            resetable resetable2(*this);
            cond3 = m_attributeitem_395(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (cond3 && current() != '\0')
        {
            if (m_comma_attributeitem_396(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: , ({ Token: , (,)}), $ref: attribute-item (XCG.Parsing.Production) }", depth);
                return false;
            }
            resetable resetable2(*this);
            cond3 = m_attributeitem_395(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_comma_399(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute>& actual, yaoosl::parsing::instance::attribute_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_comma_400(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute>& actual, yaoosl::parsing::instance::attribute_state& state, size_t depth)
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
bool yaoosl::parsing::instance::if401_402(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute>& actual, yaoosl::parsing::instance::attribute_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_comma_399(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_comma_400(true, actual, state, depth + 1))
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
            if (m_comma_400(false, actual, state, depth + 1))
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
bool yaoosl::parsing::instance::if403_404(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute>& actual, yaoosl::parsing::instance::attribute_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond2 = m_attributeitem_393(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_attributeitem_394(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attribute-item (XCG.Parsing.Production) }", depth);
                return false;
            }
            while397_398(true, actual, state, depth + 1);
            if401_402(true, actual, state, depth + 1);
            return true;
        }
        return true;
    }
    else
    {
        if (cond2)
        {
            if (m_attributeitem_394(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attribute-item (XCG.Parsing.Production) }", depth);
                return false;
            }
            while397_398(false, actual, state, depth + 1);
            if401_402(false, actual, state, depth + 1);
            return true;
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_squarebrackedclose_405(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attribute>& actual, yaoosl::parsing::instance::attribute_state& state, size_t depth)
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
bool yaoosl::parsing::instance::p_can_attribute(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::attribute> fake;
    attribute_state state;
    if (!m_squarebrackedopen_392(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!if403_404(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_squarebrackedclose_405(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::attribute> yaoosl::parsing::instance::p_match_attribute(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::attribute>();
    std::shared_ptr<yaoosl::parsing::instance::attribute> fake;
    attribute_state state;
    resetable resetable2(*this);
    if (m_squarebrackedopen_392(true, fake, state, depth + 1))
    {
        resetable2.reset();
        m_squarebrackedopen_392(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable3(*this);
    if (if403_404(true, fake, state, depth + 1))
    {
        resetable3.reset();
        if403_404(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    resetable resetable4(*this);
    if (m_squarebrackedclose_405(true, fake, state, depth + 1))
    {
        resetable4.reset();
        m_squarebrackedclose_405(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_attribute_406(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attributes>& actual, yaoosl::parsing::instance::attributes_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attribute(depth + 1))
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
    p_match_attribute(depth + 1);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_attribute_407(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attributes>& actual, yaoosl::parsing::instance::attributes_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_attribute(depth + 1))
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
    auto val2 = p_match_attribute(depth + 1);
    actual->items.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::while408_409(bool is_can, std::shared_ptr<yaoosl::parsing::instance::attributes>& actual, yaoosl::parsing::instance::attributes_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = m_attribute_406(true, actual, state, depth + 1);
    resetable1.reset();
    if (is_can)
    {
        while (cond3 && current() != '\0')
        {
            if (m_attribute_407(true, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attribute (XCG.Parsing.Production) }", depth);
                return false;
            }
            resetable resetable2(*this);
            cond3 = m_attribute_406(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (cond3 && current() != '\0')
        {
            if (m_attribute_407(false, actual, state, depth + 1))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: attribute (XCG.Parsing.Production) }", depth);
                return false;
            }
            resetable resetable2(*this);
            cond3 = m_attribute_406(true, actual, state, depth + 1);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::p_can_attributes(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::attributes> fake;
    attributes_state state;
    if (!while408_409(true, fake, state, depth + 1))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::attributes> yaoosl::parsing::instance::p_match_attributes(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::attributes>();
    std::shared_ptr<yaoosl::parsing::instance::attributes> fake;
    attributes_state state;
    resetable resetable2(*this);
    if (while408_409(true, fake, state, depth + 1))
    {
        resetable2.reset();
        while408_409(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_namespace_410(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth)
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
    actual->namespaces.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_conversion_411(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth)
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
    actual->conversions.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_class_412(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth)
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
    actual->classes.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_method_413(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth)
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
    actual->methods.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives414(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (m_namespace_410(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_namespace_410(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_conversion_411(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_conversion_411(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_class_412(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_class_412(false, actual, state, depth + 1);
            return true;
        }
    }
    else if (m_method_413(true, actual, state, depth + 1))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_method_413(false, actual, state, depth + 1);
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
bool yaoosl::parsing::instance::while415_416(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth)
{
    resetable resetable1(*this);
    bool cond3 = current() == '\0';
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives414(true, actual, state, depth + 1) && current() != '\0')
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
            if (!alternatives414(false, actual, state, depth + 1))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives414(true, actual, state, depth + 1))
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
    if (!while415_416(true, fake, state, depth + 1))
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
    if (while415_416(true, fake, state, depth + 1))
    {
        resetable2.reset();
        while415_416(false, actual, state, depth + 1);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)", depth);
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expchain_expchaincall_417(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain>& actual, yaoosl::parsing::instance::exp_chain_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_expchain_expchainaccess_418(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain>& actual, yaoosl::parsing::instance::exp_chain_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_expchain_expchainindexer_419(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain>& actual, yaoosl::parsing::instance::exp_chain_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_expchainstart_420(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain>& actual, yaoosl::parsing::instance::exp_chain_state& state, size_t depth)
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
    if (!m_expchainstart_420(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expchain_expchaincall_417(true, fake, state, depth + 1))
        {
        }
        else if (m_expchain_expchainaccess_418(true, fake, state, depth + 1))
        {
        }
        else if (m_expchain_expchainindexer_419(true, fake, state, depth + 1))
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
    if (!m_expchainstart_420(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expchain_expchaincall_417(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_chain>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expchain_expchaincall_417(false, actual, state, depth + 1);
        }
        else if (m_expchain_expchainaccess_418(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_chain>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expchain_expchainaccess_418(false, actual, state, depth + 1);
        }
        else if (m_expchain_expchainindexer_419(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_chain>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expchain_expchainindexer_419(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_identnavigation_dot_ident_421(bool is_can, std::shared_ptr<yaoosl::parsing::instance::ident_navigation>& actual, yaoosl::parsing::instance::ident_navigation_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_ident_422(bool is_can, std::shared_ptr<yaoosl::parsing::instance::ident_navigation>& actual, yaoosl::parsing::instance::ident_navigation_state& state, size_t depth)
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
    if (!m_ident_422(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_identnavigation_dot_ident_421(true, fake, state, depth + 1))
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
    if (!m_ident_422(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_identnavigation_dot_ident_421(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::ident_navigation>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_identnavigation_dot_ident_421(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_typenavigation_dot_ident_templateusage_423(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_navigation>& actual, yaoosl::parsing::instance::type_navigation_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_typenavigation_dot_ident_424(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_navigation>& actual, yaoosl::parsing::instance::type_navigation_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_ident_425(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_navigation>& actual, yaoosl::parsing::instance::type_navigation_state& state, size_t depth)
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
    if (!m_ident_425(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_typenavigation_dot_ident_templateusage_423(true, fake, state, depth + 1))
        {
        }
        else if (m_typenavigation_dot_ident_424(true, fake, state, depth + 1))
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
    if (!m_ident_425(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_typenavigation_dot_ident_templateusage_423(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::type_navigation>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_typenavigation_dot_ident_templateusage_423(false, actual, state, depth + 1);
        }
        else if (m_typenavigation_dot_ident_424(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::type_navigation>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_typenavigation_dot_ident_424(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expbinary3_lessthenlessthen_expunary_426(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_binary_3>& actual, yaoosl::parsing::instance::exp_binary_3_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__less_then_less_then(depth + 1);
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
    if (p_can_exp_unary(depth + 1))
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
    auto val4 = create_token(token__less_then_less_then(depth + 1).value(), tok::_LESS_THEN_LESS_THEN);
    actual->operator_ = val4;
    skip();
    auto val5 = p_match_exp_unary(depth + 1);
    actual->right = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expbinary3_greaterthengreaterthen_expunary_427(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_binary_3>& actual, yaoosl::parsing::instance::exp_binary_3_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__greater_then_greater_then(depth + 1);
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
    if (p_can_exp_unary(depth + 1))
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
    auto val4 = create_token(token__greater_then_greater_then(depth + 1).value(), tok::_GREATER_THEN_GREATER_THEN);
    actual->operator_ = val4;
    skip();
    auto val5 = p_match_exp_unary(depth + 1);
    actual->right = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expbinary3_lessthenlessthenlessthen_expunary_428(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_binary_3>& actual, yaoosl::parsing::instance::exp_binary_3_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__less_then_less_then_less_then(depth + 1);
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
    if (p_can_exp_unary(depth + 1))
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
    auto val4 = create_token(token__less_then_less_then_less_then(depth + 1).value(), tok::_LESS_THEN_LESS_THEN_LESS_THEN);
    actual->operator_ = val4;
    skip();
    auto val5 = p_match_exp_unary(depth + 1);
    actual->right = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expbinary3_greaterthengreaterthengreaterthen_expunary_429(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_binary_3>& actual, yaoosl::parsing::instance::exp_binary_3_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__greater_then_greater_then_greater_then(depth + 1);
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
    if (p_can_exp_unary(depth + 1))
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
    auto val4 = create_token(token__greater_then_greater_then_greater_then(depth + 1).value(), tok::_GREATER_THEN_GREATER_THEN_GREATER_THEN);
    actual->operator_ = val4;
    skip();
    auto val5 = p_match_exp_unary(depth + 1);
    actual->right = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expunary_430(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_binary_3>& actual, yaoosl::parsing::instance::exp_binary_3_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (p_can_exp_unary(depth + 1))
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
    auto val2 = p_match_exp_unary(depth + 1);
    actual->left = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_binary_3(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_binary_3> fake;
    exp_binary_3_state state;
    if (!m_expunary_430(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expbinary3_lessthenlessthen_expunary_426(true, fake, state, depth + 1))
        {
        }
        else if (m_expbinary3_greaterthengreaterthen_expunary_427(true, fake, state, depth + 1))
        {
        }
        else if (m_expbinary3_lessthenlessthenlessthen_expunary_428(true, fake, state, depth + 1))
        {
        }
        else if (m_expbinary3_greaterthengreaterthengreaterthen_expunary_429(true, fake, state, depth + 1))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_binary_3> yaoosl::parsing::instance::lr_match_exp_binary_3(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_binary_3>();
    std::shared_ptr<yaoosl::parsing::instance::exp_binary_3> fake;
    exp_binary_3_state state;
    if (!m_expunary_430(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expbinary3_lessthenlessthen_expunary_426(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_binary_3>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expbinary3_lessthenlessthen_expunary_426(false, actual, state, depth + 1);
        }
        else if (m_expbinary3_greaterthengreaterthen_expunary_427(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_binary_3>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expbinary3_greaterthengreaterthen_expunary_427(false, actual, state, depth + 1);
        }
        else if (m_expbinary3_lessthenlessthenlessthen_expunary_428(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_binary_3>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expbinary3_lessthenlessthenlessthen_expunary_428(false, actual, state, depth + 1);
        }
        else if (m_expbinary3_greaterthengreaterthengreaterthen_expunary_429(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_binary_3>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expbinary3_greaterthengreaterthengreaterthen_expunary_429(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expbinary2_ampersand_expbinary3_431(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_binary_2>& actual, yaoosl::parsing::instance::exp_binary_2_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__ampersand(depth + 1);
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
    if (lr_can_exp_binary_3(depth + 1))
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
    auto val4 = create_token(token__ampersand(depth + 1).value(), tok::_AMPERSAND);
    actual->operator_ = val4;
    skip();
    auto val5 = lr_match_exp_binary_3(depth + 1);
    actual->right = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expbinary3_432(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_binary_2>& actual, yaoosl::parsing::instance::exp_binary_2_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_exp_binary_3(depth + 1))
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
    auto val2 = lr_match_exp_binary_3(depth + 1);
    actual->left = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_binary_2(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_binary_2> fake;
    exp_binary_2_state state;
    if (!m_expbinary3_432(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expbinary2_ampersand_expbinary3_431(true, fake, state, depth + 1))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_binary_2> yaoosl::parsing::instance::lr_match_exp_binary_2(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_binary_2>();
    std::shared_ptr<yaoosl::parsing::instance::exp_binary_2> fake;
    exp_binary_2_state state;
    if (!m_expbinary3_432(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expbinary2_ampersand_expbinary3_431(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_binary_2>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expbinary2_ampersand_expbinary3_431(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expbinary1_verticalbar_expbinary2_433(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_binary_1>& actual, yaoosl::parsing::instance::exp_binary_1_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__vertical_bar(depth + 1);
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
    if (lr_can_exp_binary_2(depth + 1))
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
    auto val4 = create_token(token__vertical_bar(depth + 1).value(), tok::_VERTICAL_BAR);
    actual->operator_ = val4;
    skip();
    auto val5 = lr_match_exp_binary_2(depth + 1);
    actual->right = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expbinary2_434(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_binary_1>& actual, yaoosl::parsing::instance::exp_binary_1_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_exp_binary_2(depth + 1))
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
    auto val2 = lr_match_exp_binary_2(depth + 1);
    actual->left = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_binary_1(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_binary_1> fake;
    exp_binary_1_state state;
    if (!m_expbinary2_434(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expbinary1_verticalbar_expbinary2_433(true, fake, state, depth + 1))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_binary_1> yaoosl::parsing::instance::lr_match_exp_binary_1(size_t depth)
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_binary_1>();
    std::shared_ptr<yaoosl::parsing::instance::exp_binary_1> fake;
    exp_binary_1_state state;
    if (!m_expbinary2_434(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expbinary1_verticalbar_expbinary2_433(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_binary_1>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expbinary1_verticalbar_expbinary2_433(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_exparithmetic2_slash_expbinary1_435(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state, size_t depth)
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
    if (lr_can_exp_binary_1(depth + 1))
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
    auto val4 = create_token(token_slash(depth + 1).value(), tok::SLASH);
    actual->operator_ = val4;
    skip();
    auto val5 = lr_match_exp_binary_1(depth + 1);
    actual->right = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_exparithmetic2_star_expbinary1_436(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state, size_t depth)
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
    if (lr_can_exp_binary_1(depth + 1))
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
    auto val4 = create_token(token_star(depth + 1).value(), tok::STAR);
    actual->operator_ = val4;
    skip();
    auto val5 = lr_match_exp_binary_1(depth + 1);
    actual->right = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expbinary1_437(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state, size_t depth)
{
    resetable resetable1(*this);
    if (lr_can_exp_binary_1(depth + 1))
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
    auto val2 = lr_match_exp_binary_1(depth + 1);
    actual->left = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_arithmetic_2(size_t depth)
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> fake;
    exp_arithmetic_2_state state;
    if (!m_expbinary1_437(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic2_slash_expbinary1_435(true, fake, state, depth + 1))
        {
        }
        else if (m_exparithmetic2_star_expbinary1_436(true, fake, state, depth + 1))
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
    if (!m_expbinary1_437(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic2_slash_expbinary1_435(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_2>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic2_slash_expbinary1_435(false, actual, state, depth + 1);
        }
        else if (m_exparithmetic2_star_expbinary1_436(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_2>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic2_star_expbinary1_436(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_exparithmetic1_plus_exparithmetic2_438(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state, size_t depth)
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
    auto val4 = create_token(token_plus(depth + 1).value(), tok::PLUS);
    actual->operator_ = val4;
    skip();
    auto val5 = lr_match_exp_arithmetic_2(depth + 1);
    actual->right = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_exparithmetic1_minus_exparithmetic2_439(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state, size_t depth)
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
    auto val4 = create_token(token_minus(depth + 1).value(), tok::MINUS);
    actual->operator_ = val4;
    skip();
    auto val5 = lr_match_exp_arithmetic_2(depth + 1);
    actual->right = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_exparithmetic2_440(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state, size_t depth)
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
    if (!m_exparithmetic2_440(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic1_plus_exparithmetic2_438(true, fake, state, depth + 1))
        {
        }
        else if (m_exparithmetic1_minus_exparithmetic2_439(true, fake, state, depth + 1))
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
    if (!m_exparithmetic2_440(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic1_plus_exparithmetic2_438(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_1>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic1_plus_exparithmetic2_438(false, actual, state, depth + 1);
        }
        else if (m_exparithmetic1_minus_exparithmetic2_439(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_1>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic1_minus_exparithmetic2_439(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expcompare_lessthenequal_exparithmetic1_441(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth)
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
    auto val4 = create_token(token__less_then_equal(depth + 1).value(), tok::_LESS_THEN_EQUAL);
    actual->operator_ = val4;
    skip();
    auto val5 = lr_match_exp_arithmetic_1(depth + 1);
    actual->right = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expcompare_lessthen_exparithmetic1_442(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth)
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
    auto val4 = create_token(token__less_then(depth + 1).value(), tok::_LESS_THEN);
    actual->operator_ = val4;
    skip();
    auto val5 = lr_match_exp_arithmetic_1(depth + 1);
    actual->right = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expcompare_greaterthenequal_exparithmetic1_443(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth)
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
    auto val4 = create_token(token__greater_then_equal(depth + 1).value(), tok::_GREATER_THEN_EQUAL);
    actual->operator_ = val4;
    skip();
    auto val5 = lr_match_exp_arithmetic_1(depth + 1);
    actual->right = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expcompare_greaterthen_exparithmetic1_444(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth)
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
    auto val4 = create_token(token__greater_then(depth + 1).value(), tok::_GREATER_THEN);
    actual->operator_ = val4;
    skip();
    auto val5 = lr_match_exp_arithmetic_1(depth + 1);
    actual->right = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_exparithmetic1_445(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth)
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
    if (!m_exparithmetic1_445(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expcompare_lessthenequal_exparithmetic1_441(true, fake, state, depth + 1))
        {
        }
        else if (m_expcompare_lessthen_exparithmetic1_442(true, fake, state, depth + 1))
        {
        }
        else if (m_expcompare_greaterthenequal_exparithmetic1_443(true, fake, state, depth + 1))
        {
        }
        else if (m_expcompare_greaterthen_exparithmetic1_444(true, fake, state, depth + 1))
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
    if (!m_exparithmetic1_445(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expcompare_lessthenequal_exparithmetic1_441(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_lessthenequal_exparithmetic1_441(false, actual, state, depth + 1);
        }
        else if (m_expcompare_lessthen_exparithmetic1_442(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_lessthen_exparithmetic1_442(false, actual, state, depth + 1);
        }
        else if (m_expcompare_greaterthenequal_exparithmetic1_443(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_greaterthenequal_exparithmetic1_443(false, actual, state, depth + 1);
        }
        else if (m_expcompare_greaterthen_exparithmetic1_444(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_greaterthen_exparithmetic1_444(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expequality_lessthenequal_expcompare_446(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth)
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
    auto val4 = create_token(token__less_then_equal(depth + 1).value(), tok::_LESS_THEN_EQUAL);
    actual->operator_ = val4;
    skip();
    auto val5 = lr_match_exp_compare(depth + 1);
    actual->right = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expequality_lessthen_expcompare_447(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth)
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
    auto val4 = create_token(token__less_then(depth + 1).value(), tok::_LESS_THEN);
    actual->operator_ = val4;
    skip();
    auto val5 = lr_match_exp_compare(depth + 1);
    actual->right = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expequality_greaterthenequal_expcompare_448(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth)
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
    auto val4 = create_token(token__greater_then_equal(depth + 1).value(), tok::_GREATER_THEN_EQUAL);
    actual->operator_ = val4;
    skip();
    auto val5 = lr_match_exp_compare(depth + 1);
    actual->right = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expequality_greaterthen_expcompare_449(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth)
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
    auto val4 = create_token(token__greater_then(depth + 1).value(), tok::_GREATER_THEN);
    actual->operator_ = val4;
    skip();
    auto val5 = lr_match_exp_compare(depth + 1);
    actual->right = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expcompare_450(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth)
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
    if (!m_expcompare_450(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expequality_lessthenequal_expcompare_446(true, fake, state, depth + 1))
        {
        }
        else if (m_expequality_lessthen_expcompare_447(true, fake, state, depth + 1))
        {
        }
        else if (m_expequality_greaterthenequal_expcompare_448(true, fake, state, depth + 1))
        {
        }
        else if (m_expequality_greaterthen_expcompare_449(true, fake, state, depth + 1))
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
    if (!m_expcompare_450(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expequality_lessthenequal_expcompare_446(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_lessthenequal_expcompare_446(false, actual, state, depth + 1);
        }
        else if (m_expequality_lessthen_expcompare_447(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_lessthen_expcompare_447(false, actual, state, depth + 1);
        }
        else if (m_expequality_greaterthenequal_expcompare_448(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_greaterthenequal_expcompare_448(false, actual, state, depth + 1);
        }
        else if (m_expequality_greaterthen_expcompare_449(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_greaterthen_expcompare_449(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expand_ampersandampersand_expequality_451(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and>& actual, yaoosl::parsing::instance::exp_and_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__ampersand_ampersand(depth + 1);
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
    auto l5 = token__ampersand_ampersand(depth + 1).value();
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
bool yaoosl::parsing::instance::m_expequality_452(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and>& actual, yaoosl::parsing::instance::exp_and_state& state, size_t depth)
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
    if (!m_expequality_452(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expand_ampersandampersand_expequality_451(true, fake, state, depth + 1))
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
    if (!m_expequality_452(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expand_ampersandampersand_expequality_451(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_and>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expand_ampersandampersand_expequality_451(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expor_verticalbarverticalbar_expand_453(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or>& actual, yaoosl::parsing::instance::exp_or_state& state, size_t depth)
{
    resetable resetable1(*this);
    auto l2 = token__vertical_bar_vertical_bar(depth + 1);
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
    auto l5 = token__vertical_bar_vertical_bar(depth + 1).value();
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
bool yaoosl::parsing::instance::m_expequality_454(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or>& actual, yaoosl::parsing::instance::exp_or_state& state, size_t depth)
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
    if (!m_expequality_454(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expor_verticalbarverticalbar_expand_453(true, fake, state, depth + 1))
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
    if (!m_expequality_454(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expor_verticalbarverticalbar_expand_453(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_or>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expor_verticalbarverticalbar_expand_453(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expression_equal_expression_455(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expression>& actual, yaoosl::parsing::instance::expression_state& state, size_t depth)
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
bool yaoosl::parsing::instance::m_expor_456(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expression>& actual, yaoosl::parsing::instance::expression_state& state, size_t depth)
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
    if (!m_expor_456(true, fake, state, depth + 1))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expression_equal_expression_455(true, fake, state, depth + 1))
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
    if (!m_expor_456(false, actual, state, depth + 1))
    {
        report("Something moved wrong (todo: improve error messages)", depth);
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expression_equal_expression_455(true, fake, state, depth + 1))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::expression>();
                actual->value = tmp_actual3;
            }
            is_first2 = false;
            m_expression_equal_expression_455(false, actual, state, depth + 1);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
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
            default:
            {
                bool wasMatched1 = false;
                if (m_contents.length() > m_offset + 2 && m_contents[m_offset + 0] == '/' && m_contents[m_offset + 1] == '/')
                {
                    wasMatched1 = true;
                    for (size_t i2 = 0; i2 < 2; i2++)
                    {
                        switch (m_contents[m_offset])
                        {
                            case '\r':
                            case '\t':
                            case ' ': m_column++; m_offset++; break;
                            case '\n': m_line++; m_column = 1; m_offset++; break;
                            default: m_column++; m_offset++; break;
                        }
                    }
                    while (m_contents.length() > m_offset + 2 && !(m_contents[m_offset + 0] == '\n'))
                    {
                        switch (m_contents[m_offset])
                        {
                            case '\r':
                            case '\t':
                            case ' ': m_column++; m_offset++; break;
                            case '\n': m_line++; m_column = 1; m_offset++; break;
                            default: m_column++; m_offset++; break;
                        }
                    }
                    for (size_t i2 = 0; i2 < 1; i2++)
                    {
                        switch (m_contents[m_offset])
                        {
                            case '\r':
                            case '\t':
                            case ' ': m_column++; m_offset++; break;
                            case '\n': m_line++; m_column = 1; m_offset++; break;
                            default: m_column++; m_offset++; break;
                        }
                    }
                }
                if (m_contents.length() > m_offset + 2 && m_contents[m_offset + 0] == '/' && m_contents[m_offset + 1] == '*')
                {
                    wasMatched1 = true;
                    for (size_t i3 = 0; i3 < 2; i3++)
                    {
                        switch (m_contents[m_offset])
                        {
                            case '\r':
                            case '\t':
                            case ' ': m_column++; m_offset++; break;
                            case '\n': m_line++; m_column = 1; m_offset++; break;
                            default: m_column++; m_offset++; break;
                        }
                    }
                    while (m_contents.length() > m_offset + 2 && !(m_contents[m_offset + 0] == '*' && m_contents[m_offset + 1] == '/'))
                    {
                        switch (m_contents[m_offset])
                        {
                            case '\r':
                            case '\t':
                            case ' ': m_column++; m_offset++; break;
                            case '\n': m_line++; m_column = 1; m_offset++; break;
                            default: m_column++; m_offset++; break;
                        }
                    }
                    for (size_t i3 = 0; i3 < 2; i3++)
                    {
                        switch (m_contents[m_offset])
                        {
                            case '\r':
                            case '\t':
                            case ' ': m_column++; m_offset++; break;
                            case '\n': m_line++; m_column = 1; m_offset++; break;
                            default: m_column++; m_offset++; break;
                        }
                    }
                }
                if (!wasMatched1)
                {
                    return;
                }
            }
        }
    }
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
    skip();
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
        case 1:
        output.push_back(std::string("  ") + "token (L" + std::to_string(std::get<token>(node->part).line) + "; C" + std::to_string(std::get<token>(node->part).column) + "; O" + std::to_string(std::get<token>(node->part).offset) + ") `" + std::string(contents.substr(std::get<token>(node->part).offset, std::get<token>(node->part).length).begin(), contents.substr(std::get<token>(node->part).offset, std::get<token>(node->part).length).end()) + "`");
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<type_match> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("type_match:");
    if (node->is_array.has_value())
    {
        output.push_back(std::string("  ") + std::to_string(node->is_array.value()));
    }
    if (node->base)
    {
        auto lines = create_string_tree(node->base, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [base]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->array_size)
    {
        auto lines = create_string_tree(node->array_size, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [array_size]" "\u001b[0m" : line));
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<string_literal> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("string_literal:");
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->prefix.line) + "; C" + std::to_string(node->prefix.column) + "; O" + std::to_string(node->prefix.offset) + ") `" + std::string(contents.substr(node->prefix.offset, node->prefix.length).begin(), contents.substr(node->prefix.offset, node->prefix.length).end()) + "`");
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->value.line) + "; C" + std::to_string(node->value.column) + "; O" + std::to_string(node->value.offset) + ") `" + std::string(contents.substr(node->value.offset, node->value.length).begin(), contents.substr(node->value.offset, node->value.length).end()) + "`");
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->postfix.line) + "; C" + std::to_string(node->postfix.column) + "; O" + std::to_string(node->postfix.offset) + ") `" + std::string(contents.substr(node->postfix.offset, node->postfix.length).begin(), contents.substr(node->postfix.offset, node->postfix.length).end()) + "`");
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_value> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_value:");
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
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->float_.line) + "; C" + std::to_string(node->float_.column) + "; O" + std::to_string(node->float_.offset) + ") `" + std::string(contents.substr(node->float_.offset, node->float_.length).begin(), contents.substr(node->float_.offset, node->float_.length).end()) + "`");
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->bool_.line) + "; C" + std::to_string(node->bool_.column) + "; O" + std::to_string(node->bool_.offset) + ") `" + std::string(contents.substr(node->bool_.offset, node->bool_.length).begin(), contents.substr(node->bool_.offset, node->bool_.length).end()) + "`");
    if (node->string)
    {
        auto lines = create_string_tree(node->string, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [string]" "\u001b[0m" : line));
            first = false;
        }
    }
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->int_.line) + "; C" + std::to_string(node->int_.column) + "; O" + std::to_string(node->int_.offset) + ") `" + std::string(contents.substr(node->int_.offset, node->int_.length).begin(), contents.substr(node->int_.offset, node->int_.length).end()) + "`");
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
        if (std::get<std::shared_ptr<declaration>>(node->value))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<declaration>>(node->value), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [value]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 2:
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_unary> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_unary:");
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->operator_.line) + "; C" + std::to_string(node->operator_.column) + "; O" + std::to_string(node->operator_.offset) + ") `" + std::string(contents.substr(node->operator_.offset, node->operator_.length).begin(), contents.substr(node->operator_.offset, node->operator_.length).end()) + "`");
    switch (node->value.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_unary>>(node->value))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_unary>>(node->value), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [value]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_nullar>>(node->value))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_nullar>>(node->value), contents);
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<declaration> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("declaration:");
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
    if (node->get)
    {
        auto lines = create_string_tree(node->get, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [get]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->set)
    {
        auto lines = create_string_tree(node->set, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [set]" "\u001b[0m" : line));
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<if_body> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("if_body:");
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<else_body> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("else_body:");
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<if_else> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("if_else:");
    if (node->if_)
    {
        auto lines = create_string_tree(node->if_, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [if_]" "\u001b[0m" : line));
            first = false;
        }
    }
    if (node->else_)
    {
        auto lines = create_string_tree(node->else_, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [else_]" "\u001b[0m" : line));
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
        case 1:
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
        case 2:
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<encapsulation> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("encapsulation:");
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->tok.line) + "; C" + std::to_string(node->tok.column) + "; O" + std::to_string(node->tok.offset) + ") `" + std::string(contents.substr(node->tok.offset, node->tok.length).begin(), contents.substr(node->tok.offset, node->tok.length).end()) + "`");
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
    for (auto element : node->namespaces)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [namespaces]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    for (auto element : node->conversions)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [conversions]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    for (auto element : node->classes)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [classes]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    for (auto element : node->methods)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [methods]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    if (node->att)
    {
        auto lines = create_string_tree(node->att, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [att]" "\u001b[0m" : line));
            first = false;
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
    for (auto element : node->indexers)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [indexers]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    for (auto element : node->operators_binary)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [operators_binary]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    for (auto element : node->operators_unary)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [operators_unary]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    for (auto element : node->conversions)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [conversions]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    for (auto element : node->classes)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [classes]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    for (auto element : node->constructors)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [constructors]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    for (auto element : node->destructors)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [destructors]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    for (auto element : node->copystructors)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [copystructors]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    for (auto element : node->properties)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [properties]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    for (auto element : node->methods)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [methods]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    if (node->att)
    {
        auto lines = create_string_tree(node->att, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [att]" "\u001b[0m" : line));
            first = false;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<method_arglist_item_with_default> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("method_arglist_item_with_default:");
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
    if (node->att)
    {
        auto lines = create_string_tree(node->att, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [att]" "\u001b[0m" : line));
            first = false;
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
    if (node->att)
    {
        auto lines = create_string_tree(node->att, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [att]" "\u001b[0m" : line));
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<method_arglist_indexer> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("method_arglist_indexer:");
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
    if (node->att)
    {
        auto lines = create_string_tree(node->att, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [att]" "\u001b[0m" : line));
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
    if (node->att)
    {
        auto lines = create_string_tree(node->att, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [att]" "\u001b[0m" : line));
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
    if (node->att)
    {
        auto lines = create_string_tree(node->att, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [att]" "\u001b[0m" : line));
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
    if (node->att)
    {
        auto lines = create_string_tree(node->att, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [att]" "\u001b[0m" : line));
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
    if (node->att)
    {
        auto lines = create_string_tree(node->att, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [att]" "\u001b[0m" : line));
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
    if (node->att)
    {
        auto lines = create_string_tree(node->att, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [att]" "\u001b[0m" : line));
            first = false;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<operator_binary_overload> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("operator_binary_overload:");
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
    if (node->left)
    {
        auto lines = create_string_tree(node->left, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
            first = false;
        }
    }
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->operator_.line) + "; C" + std::to_string(node->operator_.column) + "; O" + std::to_string(node->operator_.offset) + ") `" + std::string(contents.substr(node->operator_.offset, node->operator_.length).begin(), contents.substr(node->operator_.offset, node->operator_.length).end()) + "`");
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
    if (node->att)
    {
        auto lines = create_string_tree(node->att, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [att]" "\u001b[0m" : line));
            first = false;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<operator_unary_overload> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("operator_unary_overload:");
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
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->operator_.line) + "; C" + std::to_string(node->operator_.column) + "; O" + std::to_string(node->operator_.offset) + ") `" + std::string(contents.substr(node->operator_.offset, node->operator_.length).begin(), contents.substr(node->operator_.offset, node->operator_.length).end()) + "`");
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
    if (node->att)
    {
        auto lines = create_string_tree(node->att, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [att]" "\u001b[0m" : line));
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
    if (node->att)
    {
        auto lines = create_string_tree(node->att, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [att]" "\u001b[0m" : line));
            first = false;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<attribute_arg_item_a> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("attribute_arg_item_a:");
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<attribute_arg_item_b> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("attribute_arg_item_b:");
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<attribute_args> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("attribute_args:");
    for (auto element : node->args)
    {
        switch (element.index())
        {
            case 0:
            if (std::get<std::shared_ptr<attribute_arg_item_a>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<attribute_arg_item_a>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [args]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
            case 1:
            if (std::get<std::shared_ptr<attribute_arg_item_b>>(element))
            {
                auto lines = create_string_tree(std::get<std::shared_ptr<attribute_arg_item_b>>(element), contents);
                bool first = true;
                for (auto line : lines)
                {
                    output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [args]" "\u001b[0m" : line));
                    first = false;
                }
            }
            break;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<attribute_item> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("attribute_item:");
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
    if (node->args)
    {
        auto lines = create_string_tree(node->args, contents);
        bool first = true;
        for (auto line : lines)
        {
            output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [args]" "\u001b[0m" : line));
            first = false;
        }
    }
    return output;
}
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<attribute> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("attribute:");
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<attributes> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("attributes:");
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<main> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("main:");
    for (auto element : node->namespaces)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [namespaces]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    for (auto element : node->conversions)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [conversions]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    for (auto element : node->classes)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [classes]" "\u001b[0m" : line));
                first = false;
            }
        }
    }
    for (auto element : node->methods)
    {
        if (element)
        {
            auto lines = create_string_tree(element, contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [methods]" "\u001b[0m" : line));
                first = false;
            }
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_binary_3> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_binary_3:");
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_binary_3>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_binary_3>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_unary>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_unary>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->operator_.line) + "; C" + std::to_string(node->operator_.column) + "; O" + std::to_string(node->operator_.offset) + ") `" + std::string(contents.substr(node->operator_.offset, node->operator_.length).begin(), contents.substr(node->operator_.offset, node->operator_.length).end()) + "`");
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_binary_2> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_binary_2:");
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_binary_2>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_binary_2>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_binary_3>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_binary_3>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->operator_.line) + "; C" + std::to_string(node->operator_.column) + "; O" + std::to_string(node->operator_.offset) + ") `" + std::string(contents.substr(node->operator_.offset, node->operator_.length).begin(), contents.substr(node->operator_.offset, node->operator_.length).end()) + "`");
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_binary_1> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_binary_1:");
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_binary_1>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_binary_1>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_binary_2>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_binary_2>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->operator_.line) + "; C" + std::to_string(node->operator_.column) + "; O" + std::to_string(node->operator_.offset) + ") `" + std::string(contents.substr(node->operator_.offset, node->operator_.length).begin(), contents.substr(node->operator_.offset, node->operator_.length).end()) + "`");
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
std::vector<std::string> yaoosl::parsing::instance::create_string_tree(std::shared_ptr<exp_arithmetic_2> node, std::string_view contents)
{
    std::vector<std::string> output;
    output.push_back("exp_arithmetic_2:");
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
        if (std::get<std::shared_ptr<exp_binary_1>>(node->left))
        {
            auto lines = create_string_tree(std::get<std::shared_ptr<exp_binary_1>>(node->left), contents);
            bool first = true;
            for (auto line : lines)
            {
                output.push_back((first ? std::string("- ") : std::string("  ")) + (first ? line + "\u001b[30;1m" " [left]" "\u001b[0m" : line));
                first = false;
            }
        }
        break;
    }
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->operator_.line) + "; C" + std::to_string(node->operator_.column) + "; O" + std::to_string(node->operator_.offset) + ") `" + std::string(contents.substr(node->operator_.offset, node->operator_.length).begin(), contents.substr(node->operator_.offset, node->operator_.length).end()) + "`");
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
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->operator_.line) + "; C" + std::to_string(node->operator_.column) + "; O" + std::to_string(node->operator_.offset) + ") `" + std::string(contents.substr(node->operator_.offset, node->operator_.length).begin(), contents.substr(node->operator_.offset, node->operator_.length).end()) + "`");
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
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->operator_.line) + "; C" + std::to_string(node->operator_.column) + "; O" + std::to_string(node->operator_.offset) + ") `" + std::string(contents.substr(node->operator_.offset, node->operator_.length).begin(), contents.substr(node->operator_.offset, node->operator_.length).end()) + "`");
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
    output.push_back(std::string("  ") + "token (L" + std::to_string(node->operator_.line) + "; C" + std::to_string(node->operator_.column) + "; O" + std::to_string(node->operator_.offset) + ") `" + std::string(contents.substr(node->operator_.offset, node->operator_.length).begin(), contents.substr(node->operator_.offset, node->operator_.length).end()) + "`");
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
