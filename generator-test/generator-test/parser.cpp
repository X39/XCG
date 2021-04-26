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
std::optional<size_t> yaoosl::parsing::instance::token_integer()
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0')
    {
        if ('0' <= current() && current() <= '9')
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
std::optional<size_t> yaoosl::parsing::instance::token_scalar()
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        std::optional<size_t> res3 = token_integer();
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
        std::optional<size_t> res6 = token_integer();
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
std::optional<size_t> yaoosl::parsing::instance::token_slash()
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
std::optional<size_t> yaoosl::parsing::instance::token_star()
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
std::optional<size_t> yaoosl::parsing::instance::token_plus()
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
std::optional<size_t> yaoosl::parsing::instance::token_minus()
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
std::optional<size_t> yaoosl::parsing::instance::token_underscore()
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
std::optional<size_t> yaoosl::parsing::instance::token_ident()
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        if ('a' <= current() && current() <= 'z')
        {
            count2++;
            next();
            continue;
        }
        else if ('A' <= current() && current() <= 'Z')
        {
            count2++;
            next();
            continue;
        }
        std::optional<size_t> res3 = token_underscore();
        if (res3.has_value())
        {
            count2++;
            for (size_t i = 0; i < res3; i++)
            {
                next();
            }
            continue;
        }
        std::optional<size_t> res4 = token_minus();
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
    while (current() != '\0' && count5 < -2147483647)
    {
        if ('a' <= current() && current() <= 'z')
        {
            count5++;
            next();
            continue;
        }
        else if ('A' <= current() && current() <= 'Z')
        {
            count5++;
            next();
            continue;
        }
        else if ('0' <= current() && current() <= '9')
        {
            count5++;
            next();
            continue;
        }
        std::optional<size_t> res6 = token_underscore();
        if (res6.has_value())
        {
            count5++;
            for (size_t i = 0; i < res6; i++)
            {
                next();
            }
            continue;
        }
        std::optional<size_t> res7 = token_minus();
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
    auto resultVariable8 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable8;
}
std::optional<size_t> yaoosl::parsing::instance::token__round_bracked_open()
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
    auto resultVariable9 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable9;
}
std::optional<size_t> yaoosl::parsing::instance::token__round_bracked_close()
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
    auto resultVariable10 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable10;
}
std::optional<size_t> yaoosl::parsing::instance::token__comma()
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
    auto resultVariable11 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable11;
}
std::optional<size_t> yaoosl::parsing::instance::token__less_then_equal()
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
    auto resultVariable12 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable12;
}
std::optional<size_t> yaoosl::parsing::instance::token__less_then()
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
    auto resultVariable13 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable13;
}
std::optional<size_t> yaoosl::parsing::instance::token__greater_then_equal()
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
    auto resultVariable14 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable14;
}
std::optional<size_t> yaoosl::parsing::instance::token__greater_then()
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
    auto resultVariable15 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable15;
}
std::optional<size_t> yaoosl::parsing::instance::token__and()
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
    auto resultVariable16 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable16;
}
std::optional<size_t> yaoosl::parsing::instance::token__or()
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
    auto resultVariable17 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable17;
}
std::optional<size_t> yaoosl::parsing::instance::token__equal()
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
std::optional<size_t> yaoosl::parsing::instance::token__return()
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
    auto resultVariable19 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable19;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_77()
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
    auto resultVariable20 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable20;
}
std::optional<size_t> yaoosl::parsing::instance::token__curly_bracked_open()
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
    auto resultVariable21 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable21;
}
std::optional<size_t> yaoosl::parsing::instance::token__curly_bracked_close()
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
    auto resultVariable22 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable22;
}
std::optional<size_t> yaoosl::parsing::instance::token__func()
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
    auto resultVariable23 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable23;
}
std::optional<size_t> yaoosl::parsing::instance::token__while()
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
    auto resultVariable24 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable24;
}
std::optional<size_t> yaoosl::parsing::instance::token__if()
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
    auto resultVariable25 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable25;
}
std::optional<size_t> yaoosl::parsing::instance::token__else()
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
    auto resultVariable26 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable26;
}
bool yaoosl::parsing::instance::m_ident_roundbrackedopen_27(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state)
{
    resetable resetable1(*this);
    auto l2 = token_ident();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    auto l4 = token__round_bracked_open();
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
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val6 = create_token(token_ident().value(), tok::IDENT);
    actual->method = val6;
    skip();
    auto l8 = token__round_bracked_open().value();
    for (;l8 != 0; l8--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expression_28(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state)
{
    resetable resetable1(*this);
    if (p_can_expression())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_expression();
    actual->args.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_comma_expression_29(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__comma();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (p_can_expression())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_expression();
    actual->args.push_back(val6);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_roundbrackedclose_30(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__round_bracked_close();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_close().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::while31_32(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state)
{
    resetable resetable1(*this);
    bool cond3 = m_roundbrackedclose_30(true, actual, state);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            if (m_comma_expression_29(true, actual, state))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: , ({ Token: , (,)}), $ref: expression (XCG.Parsing.Production) }");
                return false;
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_30(true, actual, state);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (m_comma_expression_29(false, actual, state))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: , ({ Token: , (,)}), $ref: expression (XCG.Parsing.Production) }");
                return false;
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_30(true, actual, state);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_expression_33(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state)
{
    resetable resetable1(*this);
    if (p_can_expression())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    p_match_expression();
    skip();
    return true;
}
bool yaoosl::parsing::instance::if34_35(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state)
{
    resetable resetable1(*this);
    bool cond2 = m_expression_33(true, actual, state);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_expression_28(true, actual, state))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: expression (XCG.Parsing.Production) }");
                return false;
            }
            while31_32(true, actual, state);
            return true;
        }
        return false;
    }
    else
    {
        if (cond2)
        {
            if (m_expression_28(false, actual, state))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: expression (XCG.Parsing.Production) }");
                return false;
            }
            while31_32(false, actual, state);
            return true;
        }
        return false;
    }
}
bool yaoosl::parsing::instance::m_roundbrackedclose_36(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__round_bracked_close();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_close().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_call()
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::call> fake;
    call_state state;
    if (!m_ident_roundbrackedopen_27(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    else if (!if34_35(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_roundbrackedclose_36(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::call> yaoosl::parsing::instance::p_match_call()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::call>();
    std::shared_ptr<yaoosl::parsing::instance::call> fake;
    call_state state;
    resetable resetable2(*this);
    if (m_ident_roundbrackedopen_27(true, fake, state))
    {
        resetable2.reset();
        m_ident_roundbrackedopen_27(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    resetable resetable3(*this);
    if (if34_35(true, fake, state))
    {
        resetable3.reset();
        if34_35(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    resetable resetable4(*this);
    if (m_roundbrackedclose_36(true, fake, state))
    {
        resetable4.reset();
        m_roundbrackedclose_36(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_roundbrackedopen_statement_roundbrackedclose_37(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__round_bracked_open();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (p_can_statement())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    auto l4 = token__round_bracked_close();
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
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l7 = token__round_bracked_open().value();
    for (;l7 != 0; l7--)
    {
        next();
    }
    skip();
    auto val8 = p_match_statement();
    actual->value = val8;
    skip();
    auto l10 = token__round_bracked_close().value();
    for (;l10 != 0; l10--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_scalar_38(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state)
{
    resetable resetable1(*this);
    auto l2 = token_scalar();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_scalar().value(), tok::SCALAR);
    actual->value = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_integer_39(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state)
{
    resetable resetable1(*this);
    auto l2 = token_integer();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_integer().value(), tok::INTEGER);
    actual->value = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_call_40(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state)
{
    resetable resetable1(*this);
    if (p_can_call())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_call();
    actual->value = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_ident_41(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state)
{
    resetable resetable1(*this);
    auto l2 = token_ident();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_ident().value(), tok::IDENT);
    actual->value = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives42(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state)
{
    resetable resetable1(*this);
    if (m_roundbrackedopen_statement_roundbrackedclose_37(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_roundbrackedopen_statement_roundbrackedclose_37(false, actual, state);
            return true;
        }
    }
    else if (m_scalar_38(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_scalar_38(false, actual, state);
            return true;
        }
    }
    else if (m_integer_39(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_integer_39(false, actual, state);
            return true;
        }
    }
    else if (m_call_40(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_call_40(false, actual, state);
            return true;
        }
    }
    else if (m_ident_41(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_ident_41(false, actual, state);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_exp_nullar()
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_nullar> fake;
    exp_nullar_state state;
    if (!alternatives42(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::exp_nullar> yaoosl::parsing::instance::p_match_exp_nullar()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_nullar>();
    std::shared_ptr<yaoosl::parsing::instance::exp_nullar> fake;
    exp_nullar_state state;
    resetable resetable2(*this);
    if (alternatives42(true, fake, state))
    {
        resetable2.reset();
        alternatives42(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_equal_statement_43(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_assignment>& actual, yaoosl::parsing::instance::exp_assignment_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__equal();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (p_can_statement())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token__equal().value(), tok::_EQUAL);
    actual->name = val4;
    skip();
    auto val5 = p_match_statement();
    actual->value = val5;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_exp_assignment()
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_assignment> fake;
    exp_assignment_state state;
    if (!m_equal_statement_43(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::exp_assignment> yaoosl::parsing::instance::p_match_exp_assignment()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_assignment>();
    std::shared_ptr<yaoosl::parsing::instance::exp_assignment> fake;
    exp_assignment_state state;
    resetable resetable2(*this);
    if (m_equal_statement_43(true, fake, state))
    {
        resetable2.reset();
        m_equal_statement_43(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_return_expor_44(bool is_can, std::shared_ptr<yaoosl::parsing::instance::return_statement>& actual, yaoosl::parsing::instance::return_statement_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__return();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (lr_can_exp_or())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__return().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_or();
    actual->expression = val6;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_return_statement()
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::return_statement> fake;
    return_statement_state state;
    if (!m_return_expor_44(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::return_statement> yaoosl::parsing::instance::p_match_return_statement()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::return_statement>();
    std::shared_ptr<yaoosl::parsing::instance::return_statement> fake;
    return_statement_state state;
    resetable resetable2(*this);
    if (m_return_expor_44(true, fake, state))
    {
        resetable2.reset();
        m_return_expor_44(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expassignment_45(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expression>& actual, yaoosl::parsing::instance::expression_state& state)
{
    resetable resetable1(*this);
    if (p_can_exp_assignment())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_exp_assignment();
    actual->expression = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expor_46(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expression>& actual, yaoosl::parsing::instance::expression_state& state)
{
    resetable resetable1(*this);
    if (lr_can_exp_or())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_exp_or();
    actual->expression = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives47(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expression>& actual, yaoosl::parsing::instance::expression_state& state)
{
    resetable resetable1(*this);
    if (m_expassignment_45(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_expassignment_45(false, actual, state);
            return true;
        }
    }
    else if (m_expor_46(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_expor_46(false, actual, state);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_expression()
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::expression> fake;
    expression_state state;
    if (!alternatives47(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::expression> yaoosl::parsing::instance::p_match_expression()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::expression>();
    std::shared_ptr<yaoosl::parsing::instance::expression> fake;
    expression_state state;
    resetable resetable2(*this);
    if (alternatives47(true, fake, state))
    {
        resetable2.reset();
        alternatives47(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_returnstatement_auto77_48(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state)
{
    resetable resetable1(*this);
    if (p_can_return_statement())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    auto l2 = token__auto_77();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = p_match_return_statement();
    actual->expression = val4;
    skip();
    auto l6 = token__auto_77().value();
    for (;l6 != 0; l6--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expression_auto77_49(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state)
{
    resetable resetable1(*this);
    if (p_can_expression())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    auto l2 = token__auto_77();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = p_match_expression();
    actual->expression = val4;
    skip();
    auto l6 = token__auto_77().value();
    for (;l6 != 0; l6--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_auto77_50(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_77();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__auto_77().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives51(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state)
{
    resetable resetable1(*this);
    if (m_returnstatement_auto77_48(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_returnstatement_auto77_48(false, actual, state);
            return true;
        }
    }
    else if (m_expression_auto77_49(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_expression_auto77_49(false, actual, state);
            return true;
        }
    }
    else if (m_auto77_50(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_auto77_50(false, actual, state);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_statement()
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::statement> fake;
    statement_state state;
    if (!alternatives51(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::statement> yaoosl::parsing::instance::p_match_statement()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::statement>();
    std::shared_ptr<yaoosl::parsing::instance::statement> fake;
    statement_state state;
    resetable resetable2(*this);
    if (alternatives51(true, fake, state))
    {
        resetable2.reset();
        alternatives51(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_ident_52(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function_arg>& actual, yaoosl::parsing::instance::function_arg_state& state)
{
    resetable resetable1(*this);
    auto l2 = token_ident();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val4 = create_token(token_ident().value(), tok::IDENT);
    actual->name = val4;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_function_arg()
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::function_arg> fake;
    function_arg_state state;
    if (!m_ident_52(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::function_arg> yaoosl::parsing::instance::p_match_function_arg()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::function_arg>();
    std::shared_ptr<yaoosl::parsing::instance::function_arg> fake;
    function_arg_state state;
    resetable resetable2(*this);
    if (m_ident_52(true, fake, state))
    {
        resetable2.reset();
        m_ident_52(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_curlybrackedopen_53(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__curly_bracked_open();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_open().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_controlstructure_54(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state)
{
    resetable resetable1(*this);
    if (p_can_control_structure())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_control_structure();
    actual->body.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_statement_55(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state)
{
    resetable resetable1(*this);
    if (p_can_statement())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_statement();
    actual->body.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives56(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state)
{
    resetable resetable1(*this);
    if (m_controlstructure_54(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_controlstructure_54(false, actual, state);
            return true;
        }
    }
    else if (m_statement_55(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_statement_55(false, actual, state);
            return true;
        }
    }
    else if (!is_can)
    {
        report("Failed to match one of the following: { control-structure, statement }");
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_curlybrackedclose_57(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__curly_bracked_close();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::while58_59(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state)
{
    resetable resetable1(*this);
    bool cond3 = m_curlybrackedclose_57(true, actual, state);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives56(true, actual, state) && current() != '\0')
            {
                next();
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_57(true, actual, state);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (!alternatives56(false, actual, state))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives56(true, actual, state))
                    {
                        resetable4.reset();
                        break;
                    }
                    next();
                }
            }
            resetable resetable2(*this);
            cond3 = m_curlybrackedclose_57(true, actual, state);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_curlybrackedclose_60(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__curly_bracked_close();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__curly_bracked_close().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_scope()
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::scope> fake;
    scope_state state;
    if (!m_curlybrackedopen_53(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    else if (!while58_59(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_curlybrackedclose_60(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::scope> yaoosl::parsing::instance::p_match_scope()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::scope>();
    std::shared_ptr<yaoosl::parsing::instance::scope> fake;
    scope_state state;
    resetable resetable2(*this);
    if (m_curlybrackedopen_53(true, fake, state))
    {
        resetable2.reset();
        m_curlybrackedopen_53(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    resetable resetable3(*this);
    if (while58_59(true, fake, state))
    {
        resetable3.reset();
        while58_59(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    resetable resetable4(*this);
    if (m_curlybrackedclose_60(true, fake, state))
    {
        resetable4.reset();
        m_curlybrackedclose_60(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_func_ident_roundbrackedopen_61(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__func();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    auto l4 = token_ident();
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
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    auto l6 = token__round_bracked_open();
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
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l9 = token__func().value();
    for (;l9 != 0; l9--)
    {
        next();
    }
    skip();
    auto val10 = create_token(token_ident().value(), tok::IDENT);
    actual->name = val10;
    skip();
    auto l12 = token__round_bracked_open().value();
    for (;l12 != 0; l12--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_functionarg_62(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state)
{
    resetable resetable1(*this);
    if (p_can_function_arg())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_function_arg();
    actual->args.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_comma_functionarg_63(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__comma();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (p_can_function_arg())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__comma().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_function_arg();
    actual->args.push_back(val6);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_roundbrackedclose_64(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__round_bracked_close();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_close().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::while65_66(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state)
{
    resetable resetable1(*this);
    bool cond3 = m_roundbrackedclose_64(true, actual, state);
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            if (m_comma_functionarg_63(true, actual, state))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: , ({ Token: , (,)}), $ref: function-arg (XCG.Parsing.Production) }");
                return false;
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_64(true, actual, state);
            resetable2.reset();
        }
        return true;
    }
    else
    {
        while (!cond3 && current() != '\0')
        {
            if (m_comma_functionarg_63(false, actual, state))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: , ({ Token: , (,)}), $ref: function-arg (XCG.Parsing.Production) }");
                return false;
            }
            resetable resetable2(*this);
            cond3 = m_roundbrackedclose_64(true, actual, state);
            resetable2.reset();
        }
        return true;
    }
}
bool yaoosl::parsing::instance::m_functionarg_67(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state)
{
    resetable resetable1(*this);
    if (p_can_function_arg())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    p_match_function_arg();
    skip();
    return true;
}
bool yaoosl::parsing::instance::if68_69(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state)
{
    resetable resetable1(*this);
    bool cond2 = m_functionarg_67(true, actual, state);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_functionarg_62(true, actual, state))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: function-arg (XCG.Parsing.Production) }");
                return false;
            }
            while65_66(true, actual, state);
            return true;
        }
        return false;
    }
    else
    {
        if (cond2)
        {
            if (m_functionarg_62(false, actual, state))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: function-arg (XCG.Parsing.Production) }");
                return false;
            }
            while65_66(false, actual, state);
            return true;
        }
        return false;
    }
}
bool yaoosl::parsing::instance::m_roundbrackedclose_scope_70(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__round_bracked_close();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (p_can_scope())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__round_bracked_close().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_scope();
    actual->body = val6;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_function()
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::function> fake;
    function_state state;
    if (!m_func_ident_roundbrackedopen_61(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    else if (!if68_69(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_roundbrackedclose_scope_70(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::function> yaoosl::parsing::instance::p_match_function()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::function>();
    std::shared_ptr<yaoosl::parsing::instance::function> fake;
    function_state state;
    resetable resetable2(*this);
    if (m_func_ident_roundbrackedopen_61(true, fake, state))
    {
        resetable2.reset();
        m_func_ident_roundbrackedopen_61(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    resetable resetable3(*this);
    if (if68_69(true, fake, state))
    {
        resetable3.reset();
        if68_69(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    resetable resetable4(*this);
    if (m_roundbrackedclose_scope_70(true, fake, state))
    {
        resetable4.reset();
        m_roundbrackedclose_scope_70(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_while_roundbrackedopen_statement_roundbrackedclose_scope_71(bool is_can, std::shared_ptr<yaoosl::parsing::instance::while_loop>& actual, yaoosl::parsing::instance::while_loop_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__while();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    auto l4 = token__round_bracked_open();
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
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (p_can_statement())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    auto l6 = token__round_bracked_close();
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
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (p_can_scope())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l9 = token__while().value();
    for (;l9 != 0; l9--)
    {
        next();
    }
    skip();
    auto l11 = token__round_bracked_open().value();
    for (;l11 != 0; l11--)
    {
        next();
    }
    skip();
    auto val12 = p_match_statement();
    actual->condition = val12;
    skip();
    auto l14 = token__round_bracked_close().value();
    for (;l14 != 0; l14--)
    {
        next();
    }
    skip();
    auto val15 = p_match_scope();
    actual->body = val15;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_while_loop()
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::while_loop> fake;
    while_loop_state state;
    if (!m_while_roundbrackedopen_statement_roundbrackedclose_scope_71(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::while_loop> yaoosl::parsing::instance::p_match_while_loop()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::while_loop>();
    std::shared_ptr<yaoosl::parsing::instance::while_loop> fake;
    while_loop_state state;
    resetable resetable2(*this);
    if (m_while_roundbrackedopen_statement_roundbrackedclose_scope_71(true, fake, state))
    {
        resetable2.reset();
        m_while_roundbrackedopen_statement_roundbrackedclose_scope_71(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_if_roundbrackedopen_statement_roundbrackedclose_72(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__if();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    auto l4 = token__round_bracked_open();
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
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (p_can_statement())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    auto l6 = token__round_bracked_close();
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
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l9 = token__if().value();
    for (;l9 != 0; l9--)
    {
        next();
    }
    skip();
    auto l11 = token__round_bracked_open().value();
    for (;l11 != 0; l11--)
    {
        next();
    }
    skip();
    auto val12 = p_match_statement();
    actual->condition = val12;
    skip();
    auto l14 = token__round_bracked_close().value();
    for (;l14 != 0; l14--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_scope_73(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state)
{
    resetable resetable1(*this);
    if (p_can_scope())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_scope();
    actual->if_body = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_controlstructure_74(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state)
{
    resetable resetable1(*this);
    if (p_can_control_structure())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_control_structure();
    actual->if_body = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_statement_75(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state)
{
    resetable resetable1(*this);
    if (p_can_statement())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_statement();
    actual->if_body = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives76(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state)
{
    resetable resetable1(*this);
    if (m_scope_73(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_scope_73(false, actual, state);
            return true;
        }
    }
    else if (m_controlstructure_74(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_controlstructure_74(false, actual, state);
            return true;
        }
    }
    else if (m_statement_75(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_statement_75(false, actual, state);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_else_77(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__else();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__else().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_scope_78(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state)
{
    resetable resetable1(*this);
    if (p_can_scope())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_scope();
    actual->else_body = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_controlstructure_79(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state)
{
    resetable resetable1(*this);
    if (p_can_control_structure())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_control_structure();
    actual->else_body = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_statement_80(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state)
{
    resetable resetable1(*this);
    if (p_can_statement())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_statement();
    actual->else_body = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives81(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state)
{
    resetable resetable1(*this);
    if (m_scope_78(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_scope_78(false, actual, state);
            return true;
        }
    }
    else if (m_controlstructure_79(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_controlstructure_79(false, actual, state);
            return true;
        }
    }
    else if (m_statement_80(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_statement_80(false, actual, state);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_else_82(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__else();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__else().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::if83_84(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state)
{
    resetable resetable1(*this);
    bool cond2 = m_else_82(true, actual, state);
    resetable1.reset();
    if (is_can)
    {
        if (cond2)
        {
            if (m_else_77(true, actual, state))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: else ({ Token: else (else)}) }");
                return false;
            }
            alternatives81(true, actual, state);
            return true;
        }
        return false;
    }
    else
    {
        if (cond2)
        {
            if (m_else_77(false, actual, state))
            {
                skip();
            }
            else if (is_can)
            {
                return false;
            }
            else
            {
                report("Failed to match { $ref: else ({ Token: else (else)}) }");
                return false;
            }
            alternatives81(false, actual, state);
            return true;
        }
        return false;
    }
}
bool yaoosl::parsing::instance::p_can_if_else()
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::if_else> fake;
    if_else_state state;
    if (!m_if_roundbrackedopen_statement_roundbrackedclose_72(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    else if (!alternatives76(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    else if (!if83_84(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::if_else> yaoosl::parsing::instance::p_match_if_else()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::if_else>();
    std::shared_ptr<yaoosl::parsing::instance::if_else> fake;
    if_else_state state;
    resetable resetable2(*this);
    if (m_if_roundbrackedopen_statement_roundbrackedclose_72(true, fake, state))
    {
        resetable2.reset();
        m_if_roundbrackedopen_statement_roundbrackedclose_72(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    resetable resetable3(*this);
    if (alternatives76(true, fake, state))
    {
        resetable3.reset();
        alternatives76(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    resetable resetable4(*this);
    if (if83_84(true, fake, state))
    {
        resetable4.reset();
        if83_84(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_function_85(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state)
{
    resetable resetable1(*this);
    if (p_can_function())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_function();
    actual->content = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_whileloop_86(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state)
{
    resetable resetable1(*this);
    if (p_can_while_loop())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_while_loop();
    actual->content = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_ifelse_87(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state)
{
    resetable resetable1(*this);
    if (p_can_if_else())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_if_else();
    actual->content = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_scope_88(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state)
{
    resetable resetable1(*this);
    if (p_can_scope())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_scope();
    actual->content = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives89(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state)
{
    resetable resetable1(*this);
    if (m_function_85(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_function_85(false, actual, state);
            return true;
        }
    }
    else if (m_whileloop_86(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_whileloop_86(false, actual, state);
            return true;
        }
    }
    else if (m_ifelse_87(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_ifelse_87(false, actual, state);
            return true;
        }
    }
    else if (m_scope_88(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_scope_88(false, actual, state);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_control_structure()
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::control_structure> fake;
    control_structure_state state;
    if (!alternatives89(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::control_structure> yaoosl::parsing::instance::p_match_control_structure()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::control_structure>();
    std::shared_ptr<yaoosl::parsing::instance::control_structure> fake;
    control_structure_state state;
    resetable resetable2(*this);
    if (alternatives89(true, fake, state))
    {
        resetable2.reset();
        alternatives89(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_controlstructure_90(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state)
{
    resetable resetable1(*this);
    if (p_can_control_structure())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_control_structure();
    actual->content.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_statement_91(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state)
{
    resetable resetable1(*this);
    if (p_can_statement())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_statement();
    actual->content.push_back(val2);
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives92(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state)
{
    resetable resetable1(*this);
    if (m_controlstructure_90(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_controlstructure_90(false, actual, state);
            return true;
        }
    }
    else if (m_statement_91(true, actual, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_statement_91(false, actual, state);
            return true;
        }
    }
    else if (!is_can)
    {
        report("Failed to match one of the following: { control-structure, statement }");
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::while93_94(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state)
{
    resetable resetable1(*this);
    bool cond3 = current() == '\0';
    resetable1.reset();
    if (is_can)
    {
        while (!cond3 && current() != '\0')
        {
            while (!alternatives92(true, actual, state) && current() != '\0')
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
            if (!alternatives92(false, actual, state))
            {
                while (current() != '\0')
                {
                    resetable resetable4(*this);
                    if (alternatives92(true, actual, state))
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
bool yaoosl::parsing::instance::p_can_main()
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::main> fake;
    main_state state;
    if (!while93_94(true, fake, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::main> yaoosl::parsing::instance::p_match_main()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::main>();
    std::shared_ptr<yaoosl::parsing::instance::main> fake;
    main_state state;
    resetable resetable2(*this);
    if (while93_94(true, fake, state))
    {
        resetable2.reset();
        while93_94(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_exparithmetic2_slash_expnullar_95(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state)
{
    resetable resetable1(*this);
    auto l2 = token_slash();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (p_can_exp_nullar())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token_slash().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_exp_nullar();
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op = '/';
    }
    return true;
}
bool yaoosl::parsing::instance::m_exparithmetic2_star_expnullar_96(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state)
{
    resetable resetable1(*this);
    auto l2 = token_star();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (p_can_exp_nullar())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token_star().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_exp_nullar();
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op = '*';
    }
    return true;
}
bool yaoosl::parsing::instance::m_expnullar_97(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state)
{
    resetable resetable1(*this);
    if (p_can_exp_nullar())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = p_match_exp_nullar();
    actual->left = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_arithmetic_2()
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> fake;
    exp_arithmetic_2_state state;
    if (!m_expnullar_97(true, fake, state))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic2_slash_expnullar_95(true, fake, state))
        {
        }
        else if (m_exparithmetic2_star_expnullar_96(true, fake, state))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> yaoosl::parsing::instance::lr_match_exp_arithmetic_2()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_2>();
    std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> fake;
    exp_arithmetic_2_state state;
    if (!m_expnullar_97(false, actual, state))
    {
        report("Something moved wrong (todo: improve error messages)");
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic2_slash_expnullar_95(true, fake, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_2>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic2_slash_expnullar_95(false, actual, state);
        }
        else if (m_exparithmetic2_star_expnullar_96(true, fake, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_2>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic2_star_expnullar_96(false, actual, state);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_exparithmetic1_plus_exparithmetic2_98(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state)
{
    resetable resetable1(*this);
    auto l2 = token_plus();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (lr_can_exp_arithmetic_2())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token_plus().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_arithmetic_2();
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op = '+';
    }
    return true;
}
bool yaoosl::parsing::instance::m_exparithmetic1_minus_exparithmetic2_99(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state)
{
    resetable resetable1(*this);
    auto l2 = token_minus();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (lr_can_exp_arithmetic_2())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token_minus().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_arithmetic_2();
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op = '-';
    }
    return true;
}
bool yaoosl::parsing::instance::m_exparithmetic2_100(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state)
{
    resetable resetable1(*this);
    if (lr_can_exp_arithmetic_2())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_exp_arithmetic_2();
    actual->left = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_arithmetic_1()
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> fake;
    exp_arithmetic_1_state state;
    if (!m_exparithmetic2_100(true, fake, state))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic1_plus_exparithmetic2_98(true, fake, state))
        {
        }
        else if (m_exparithmetic1_minus_exparithmetic2_99(true, fake, state))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> yaoosl::parsing::instance::lr_match_exp_arithmetic_1()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_1>();
    std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> fake;
    exp_arithmetic_1_state state;
    if (!m_exparithmetic2_100(false, actual, state))
    {
        report("Something moved wrong (todo: improve error messages)");
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic1_plus_exparithmetic2_98(true, fake, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_1>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic1_plus_exparithmetic2_98(false, actual, state);
        }
        else if (m_exparithmetic1_minus_exparithmetic2_99(true, fake, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_1>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic1_minus_exparithmetic2_99(false, actual, state);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expcompare_lessthenequal_exparithmetic1_101(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__less_then_equal();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (lr_can_exp_arithmetic_1())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__less_then_equal().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_arithmetic_1();
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
bool yaoosl::parsing::instance::m_expcompare_lessthen_exparithmetic1_102(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__less_then();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (lr_can_exp_arithmetic_1())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__less_then().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_arithmetic_1();
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op1 = '<';
    }
    return true;
}
bool yaoosl::parsing::instance::m_expcompare_greaterthenequal_exparithmetic1_103(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__greater_then_equal();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (lr_can_exp_arithmetic_1())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__greater_then_equal().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_arithmetic_1();
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
bool yaoosl::parsing::instance::m_expcompare_greaterthen_exparithmetic1_104(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__greater_then();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (lr_can_exp_arithmetic_1())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__greater_then().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_arithmetic_1();
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op1 = '>';
    }
    return true;
}
bool yaoosl::parsing::instance::m_exparithmetic1_105(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state)
{
    resetable resetable1(*this);
    if (lr_can_exp_arithmetic_1())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_exp_arithmetic_1();
    actual->left = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_compare()
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_compare> fake;
    exp_compare_state state;
    if (!m_exparithmetic1_105(true, fake, state))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expcompare_lessthenequal_exparithmetic1_101(true, fake, state))
        {
        }
        else if (m_expcompare_lessthen_exparithmetic1_102(true, fake, state))
        {
        }
        else if (m_expcompare_greaterthenequal_exparithmetic1_103(true, fake, state))
        {
        }
        else if (m_expcompare_greaterthen_exparithmetic1_104(true, fake, state))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_compare> yaoosl::parsing::instance::lr_match_exp_compare()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
    std::shared_ptr<yaoosl::parsing::instance::exp_compare> fake;
    exp_compare_state state;
    if (!m_exparithmetic1_105(false, actual, state))
    {
        report("Something moved wrong (todo: improve error messages)");
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expcompare_lessthenequal_exparithmetic1_101(true, fake, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_lessthenequal_exparithmetic1_101(false, actual, state);
        }
        else if (m_expcompare_lessthen_exparithmetic1_102(true, fake, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_lessthen_exparithmetic1_102(false, actual, state);
        }
        else if (m_expcompare_greaterthenequal_exparithmetic1_103(true, fake, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_greaterthenequal_exparithmetic1_103(false, actual, state);
        }
        else if (m_expcompare_greaterthen_exparithmetic1_104(true, fake, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_greaterthen_exparithmetic1_104(false, actual, state);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expequality_lessthenequal_expcompare_106(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__less_then_equal();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (lr_can_exp_compare())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__less_then_equal().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_compare();
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
bool yaoosl::parsing::instance::m_expequality_lessthen_expcompare_107(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__less_then();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (lr_can_exp_compare())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__less_then().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_compare();
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op1 = '<';
    }
    return true;
}
bool yaoosl::parsing::instance::m_expequality_greaterthenequal_expcompare_108(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__greater_then_equal();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (lr_can_exp_compare())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__greater_then_equal().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_compare();
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
bool yaoosl::parsing::instance::m_expequality_greaterthen_expcompare_109(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__greater_then();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (lr_can_exp_compare())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__greater_then().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_compare();
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op1 = '>';
    }
    return true;
}
bool yaoosl::parsing::instance::m_expcompare_110(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state)
{
    resetable resetable1(*this);
    if (lr_can_exp_compare())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_exp_compare();
    actual->left = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_equality()
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_equality> fake;
    exp_equality_state state;
    if (!m_expcompare_110(true, fake, state))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expequality_lessthenequal_expcompare_106(true, fake, state))
        {
        }
        else if (m_expequality_lessthen_expcompare_107(true, fake, state))
        {
        }
        else if (m_expequality_greaterthenequal_expcompare_108(true, fake, state))
        {
        }
        else if (m_expequality_greaterthen_expcompare_109(true, fake, state))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_equality> yaoosl::parsing::instance::lr_match_exp_equality()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
    std::shared_ptr<yaoosl::parsing::instance::exp_equality> fake;
    exp_equality_state state;
    if (!m_expcompare_110(false, actual, state))
    {
        report("Something moved wrong (todo: improve error messages)");
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expequality_lessthenequal_expcompare_106(true, fake, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_lessthenequal_expcompare_106(false, actual, state);
        }
        else if (m_expequality_lessthen_expcompare_107(true, fake, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_lessthen_expcompare_107(false, actual, state);
        }
        else if (m_expequality_greaterthenequal_expcompare_108(true, fake, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_greaterthenequal_expcompare_108(false, actual, state);
        }
        else if (m_expequality_greaterthen_expcompare_109(true, fake, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_greaterthen_expcompare_109(false, actual, state);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expand_and_expequality_111(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and>& actual, yaoosl::parsing::instance::exp_and_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__and();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (lr_can_exp_equality())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__and().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_equality();
    actual->right = val6;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expequality_112(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and>& actual, yaoosl::parsing::instance::exp_and_state& state)
{
    resetable resetable1(*this);
    if (lr_can_exp_equality())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_exp_equality();
    actual->left = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_and()
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_and> fake;
    exp_and_state state;
    if (!m_expequality_112(true, fake, state))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expand_and_expequality_111(true, fake, state))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_and> yaoosl::parsing::instance::lr_match_exp_and()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_and>();
    std::shared_ptr<yaoosl::parsing::instance::exp_and> fake;
    exp_and_state state;
    if (!m_expequality_112(false, actual, state))
    {
        report("Something moved wrong (todo: improve error messages)");
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expand_and_expequality_111(true, fake, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_and>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expand_and_expequality_111(false, actual, state);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expor_or_expequality_113(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or>& actual, yaoosl::parsing::instance::exp_or_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__or();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (lr_can_exp_equality())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto l5 = token__or().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = lr_match_exp_equality();
    actual->right = val6;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expequality_114(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or>& actual, yaoosl::parsing::instance::exp_or_state& state)
{
    resetable resetable1(*this);
    if (lr_can_exp_equality())
    {
        skip();
    }
    else if (is_can)
    {
        resetable1.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val2 = lr_match_exp_equality();
    actual->left = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_exp_or()
{
    resetable resetable1(*this);
    std::shared_ptr<yaoosl::parsing::instance::exp_or> fake;
    exp_or_state state;
    if (!m_expequality_114(true, fake, state))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expor_or_expequality_113(true, fake, state))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::exp_or> yaoosl::parsing::instance::lr_match_exp_or()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_or>();
    std::shared_ptr<yaoosl::parsing::instance::exp_or> fake;
    exp_or_state state;
    if (!m_expequality_114(false, actual, state))
    {
        report("Something moved wrong (todo: improve error messages)");
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expor_or_expequality_113(true, fake, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_or>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expor_or_expequality_113(false, actual, state);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
void yaoosl::parsing::instance::report(std::string_view message)
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
    return p_match_main();
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
        output.push_back(std::string("  ") + "token (L" + std::to_string(std::get<token>(node->value).line) + "; C" + std::to_string(std::get<token>(node->value).column) + "; O" + std::to_string(std::get<token>(node->value).offset) + ") `" + std::string(contents.substr(std::get<token>(node->value).offset, std::get<token>(node->value).length).begin(), contents.substr(std::get<token>(node->value).offset, std::get<token>(node->value).length).end()) + "`");
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
