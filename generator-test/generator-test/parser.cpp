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
    size_t count8 = 0;
    size_t loff9 = 0;
    while (current() != '\0' && count8 < 1)
    {
        if (m_offset >= 1 && m_contents[m_offset - 1] == '-')
        {
            count8++;
            loff9 += 1;
            continue;
        }
        break;
    }
    if (count8 < 1)
    {
        resetable1.reset();
        return {};
    }
    auto resultVariable8 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable8;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_7()
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
std::optional<size_t> yaoosl::parsing::instance::token__auto_9()
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
std::optional<size_t> yaoosl::parsing::instance::token__auto_28()
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "<=";
        if (m_contents.length() - m_offset < 2 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 2, str3, str3 + 2))
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
    auto resultVariable11 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable11;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_31()
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
    auto resultVariable12 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable12;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_34()
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = ">=";
        if (m_contents.length() - m_offset < 2 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 2, str3, str3 + 2))
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
    auto resultVariable13 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable13;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_37()
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
    auto resultVariable14 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable14;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_54()
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "and";
        if (m_contents.length() - m_offset < 3 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 3, str3, str3 + 3))
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
    auto resultVariable15 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable15;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_58()
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "or";
        if (m_contents.length() - m_offset < 2 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 2, str3, str3 + 2))
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
    auto resultVariable16 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable16;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_62()
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
    auto resultVariable17 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable17;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_67()
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
    auto resultVariable18 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable18;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_68()
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
    auto resultVariable19 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable19;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_72()
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "func";
        if (m_contents.length() - m_offset < 4 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 4, str3, str3 + 4))
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
    auto resultVariable20 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable20;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_78()
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
    auto resultVariable21 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable21;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_82()
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "while";
        if (m_contents.length() - m_offset < 5 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 5, str3, str3 + 5))
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
    auto resultVariable22 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable22;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_87()
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "if";
        if (m_contents.length() - m_offset < 2 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 2, str3, str3 + 2))
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
    auto resultVariable23 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable23;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_94()
{
    resetable resetable1(*this);
    size_t count2 = 0;
    while (current() != '\0' && count2 < 1)
    {
        const char* str3 = "else";
        if (m_contents.length() - m_offset < 4 && std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + 4, str3, str3 + 4))
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
    auto resultVariable24 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable24;
}
bool yaoosl::parsing::instance::m_auto7_statement_auto9_25(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar> actual, yaoosl::parsing::instance::exp_nullar_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_7();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l4 = token__auto_9();
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
    auto l7 = token__auto_7().value();
    for (;l7 != 0; l7--)
    {
        next();
    }
    skip();
    auto val8 = p_match_statement();
    actual->value = val8;
    skip();
    auto l10 = token__auto_9().value();
    for (;l10 != 0; l10--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_scalar_26(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar> actual, yaoosl::parsing::instance::exp_nullar_state& state)
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
bool yaoosl::parsing::instance::m_integer_27(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar> actual, yaoosl::parsing::instance::exp_nullar_state& state)
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
bool yaoosl::parsing::instance::m_ident_28(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar> actual, yaoosl::parsing::instance::exp_nullar_state& state)
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
bool yaoosl::parsing::instance::alternatives29(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar> actual, yaoosl::parsing::instance::exp_nullar_state& state)
{
    resetable resetable1(*this);
    if (m_auto7_statement_auto9_25(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_auto7_statement_auto9_25(false, actual, state);
            return true;
        }
    }
    else if (m_scalar_26(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_scalar_26(false, actual, state);
            return true;
        }
    }
    else if (m_integer_27(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_integer_27(false, actual, state);
            return true;
        }
    }
    else if (m_ident_28(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_ident_28(false, actual, state);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_exp_nullar()
{
    resetable resetable1(*this);
    exp_nullar_state state;
    if (!alternatives29(true, {}, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::exp_nullar> yaoosl::parsing::instance::p_match_exp_nullar()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_nullar>();
    exp_nullar_state state;
    resetable resetable2(*this);
    if (alternatives29(true, {}, state))
    {
        resetable2.reset();
        alternatives29(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_integer_auto62_statement_30(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_assignment> actual, yaoosl::parsing::instance::exp_assignment_state& state)
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
    auto l4 = token__auto_62();
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
    if (is_can)
    {
        return true;
    }
    resetable1.reset();
    auto val6 = create_token(token_integer().value(), tok::INTEGER);
    actual->name = val6;
    skip();
    auto l8 = token__auto_62().value();
    for (;l8 != 0; l8--)
    {
        next();
    }
    skip();
    auto val9 = p_match_statement();
    actual->value = val9;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_exp_assignment()
{
    resetable resetable1(*this);
    exp_assignment_state state;
    if (!m_integer_auto62_statement_30(true, {}, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::exp_assignment> yaoosl::parsing::instance::p_match_exp_assignment()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::exp_assignment>();
    exp_assignment_state state;
    resetable resetable2(*this);
    if (m_integer_auto62_statement_30(true, {}, state))
    {
        resetable2.reset();
        m_integer_auto62_statement_30(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expassignment_31(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement> actual, yaoosl::parsing::instance::statement_state& state)
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
    p_match_exp_assignment();
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_expor_32(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement> actual, yaoosl::parsing::instance::statement_state& state)
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
    lr_match_exp_or();
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives33(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement> actual, yaoosl::parsing::instance::statement_state& state)
{
    resetable resetable1(*this);
    if (m_expassignment_31(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_expassignment_31(false, actual, state);
            return true;
        }
    }
    else if (m_expor_32(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_expor_32(false, actual, state);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_statement()
{
    resetable resetable1(*this);
    statement_state state;
    if (!alternatives33(true, {}, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::statement> yaoosl::parsing::instance::p_match_statement()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::statement>();
    statement_state state;
    resetable resetable2(*this);
    if (alternatives33(true, {}, state))
    {
        resetable2.reset();
        alternatives33(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_ident_34(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function_arg> actual, yaoosl::parsing::instance::function_arg_state& state)
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
    function_arg_state state;
    if (!m_ident_34(true, {}, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::function_arg> yaoosl::parsing::instance::p_match_function_arg()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::function_arg>();
    function_arg_state state;
    resetable resetable2(*this);
    if (m_ident_34(true, {}, state))
    {
        resetable2.reset();
        m_ident_34(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_auto67_35(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope> actual, yaoosl::parsing::instance::scope_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_67();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l5 = token__auto_67().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_controlstructure_36(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope> actual, yaoosl::parsing::instance::scope_state& state)
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
    p_match_control_structure();
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_statement_37(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope> actual, yaoosl::parsing::instance::scope_state& state)
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
    p_match_statement();
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives38(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope> actual, yaoosl::parsing::instance::scope_state& state)
{
    resetable resetable1(*this);
    if (m_controlstructure_36(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_controlstructure_36(false, actual, state);
            return true;
        }
    }
    else if (m_statement_37(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_statement_37(false, actual, state);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_auto68_39(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope> actual, yaoosl::parsing::instance::scope_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_68();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l5 = token__auto_68().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::while40_41(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope> actual, yaoosl::parsing::instance::scope_state& state)
{
    resetable resetable1(*this);
    bool cond2 = m_auto68_39(true, {}, state);
    while (cond2)
    {
        return false;
        alternatives38(false, actual, state);
        bool cond2 = m_auto68_39(true, {}, state);
    }
    return true;
}
bool yaoosl::parsing::instance::m_auto68_42(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope> actual, yaoosl::parsing::instance::scope_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_68();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l5 = token__auto_68().value();
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
    scope_state state;
    if (!m_auto67_35(true, {}, state))
    {
        resetable1.reset();
        return false;
    }
    else if (!while40_41(true, {}, state))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_auto68_42(true, {}, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::scope> yaoosl::parsing::instance::p_match_scope()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::scope>();
    scope_state state;
    resetable resetable2(*this);
    if (m_auto67_35(true, {}, state))
    {
        resetable2.reset();
        m_auto67_35(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    resetable resetable3(*this);
    if (while40_41(true, {}, state))
    {
        resetable3.reset();
        while40_41(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    resetable resetable4(*this);
    if (m_auto68_42(true, {}, state))
    {
        resetable4.reset();
        m_auto68_42(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_auto72_ident_auto7_43(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function> actual, yaoosl::parsing::instance::function_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_72();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l6 = token__auto_7();
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
    auto l9 = token__auto_72().value();
    for (;l9 != 0; l9--)
    {
        next();
    }
    skip();
    auto val10 = create_token(token_ident().value(), tok::IDENT);
    actual->name = val10;
    skip();
    auto l12 = token__auto_7().value();
    for (;l12 != 0; l12--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_functionarg_44(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function> actual, yaoosl::parsing::instance::function_state& state)
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
    actual->args = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_auto78_functionarg_45(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function> actual, yaoosl::parsing::instance::function_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_78();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l5 = token__auto_78().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    auto val6 = p_match_function_arg();
    actual->args = val6;
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_auto9_46(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function> actual, yaoosl::parsing::instance::function_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_9();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l5 = token__auto_9().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::while47_48(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function> actual, yaoosl::parsing::instance::function_state& state)
{
    resetable resetable1(*this);
    bool cond2 = m_auto9_46(true, {}, state);
    while (cond2)
    {
        return false;
        m_auto78_functionarg_45(false, actual, state);
        bool cond2 = m_auto9_46(true, {}, state);
    }
    return true;
}
bool yaoosl::parsing::instance::m_functionarg_49(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function> actual, yaoosl::parsing::instance::function_state& state)
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
bool yaoosl::parsing::instance::if50_51(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function> actual, yaoosl::parsing::instance::function_state& state)
{
    resetable resetable1(*this);
    bool cond2 = m_functionarg_49(true, {}, state);
    if (!cond2)
    {
        return false;
    }
    m_functionarg_44(false, actual, state);
    while47_48(false, actual, state);
    return true;
}
bool yaoosl::parsing::instance::m_auto9_scope_52(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function> actual, yaoosl::parsing::instance::function_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_9();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l5 = token__auto_9().value();
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
    function_state state;
    if (!m_auto72_ident_auto7_43(true, {}, state))
    {
        resetable1.reset();
        return false;
    }
    else if (!if50_51(true, {}, state))
    {
        resetable1.reset();
        return false;
    }
    else if (!m_auto9_scope_52(true, {}, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::function> yaoosl::parsing::instance::p_match_function()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::function>();
    function_state state;
    resetable resetable2(*this);
    if (m_auto72_ident_auto7_43(true, {}, state))
    {
        resetable2.reset();
        m_auto72_ident_auto7_43(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    resetable resetable3(*this);
    if (if50_51(true, {}, state))
    {
        resetable3.reset();
        if50_51(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    resetable resetable4(*this);
    if (m_auto9_scope_52(true, {}, state))
    {
        resetable4.reset();
        m_auto9_scope_52(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_auto82_auto7_statement_auto9_scope_53(bool is_can, std::shared_ptr<yaoosl::parsing::instance::while_loop> actual, yaoosl::parsing::instance::while_loop_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_82();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l4 = token__auto_7();
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
    auto l6 = token__auto_9();
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
    auto l9 = token__auto_82().value();
    for (;l9 != 0; l9--)
    {
        next();
    }
    skip();
    auto l11 = token__auto_7().value();
    for (;l11 != 0; l11--)
    {
        next();
    }
    skip();
    auto val12 = p_match_statement();
    actual->condition = val12;
    skip();
    auto l14 = token__auto_9().value();
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
    while_loop_state state;
    if (!m_auto82_auto7_statement_auto9_scope_53(true, {}, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::while_loop> yaoosl::parsing::instance::p_match_while_loop()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::while_loop>();
    while_loop_state state;
    resetable resetable2(*this);
    if (m_auto82_auto7_statement_auto9_scope_53(true, {}, state))
    {
        resetable2.reset();
        m_auto82_auto7_statement_auto9_scope_53(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_auto87_auto7_statement_auto9_54(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual, yaoosl::parsing::instance::if_else_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_87();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l4 = token__auto_7();
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
    auto l6 = token__auto_9();
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
    auto l9 = token__auto_87().value();
    for (;l9 != 0; l9--)
    {
        next();
    }
    skip();
    auto l11 = token__auto_7().value();
    for (;l11 != 0; l11--)
    {
        next();
    }
    skip();
    auto val12 = p_match_statement();
    actual->condition = val12;
    skip();
    auto l14 = token__auto_9().value();
    for (;l14 != 0; l14--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_scope_55(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual, yaoosl::parsing::instance::if_else_state& state)
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
bool yaoosl::parsing::instance::m_controlstructure_56(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual, yaoosl::parsing::instance::if_else_state& state)
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
bool yaoosl::parsing::instance::m_statement_57(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual, yaoosl::parsing::instance::if_else_state& state)
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
bool yaoosl::parsing::instance::alternatives58(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual, yaoosl::parsing::instance::if_else_state& state)
{
    resetable resetable1(*this);
    if (m_scope_55(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_scope_55(false, actual, state);
            return true;
        }
    }
    else if (m_controlstructure_56(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_controlstructure_56(false, actual, state);
            return true;
        }
    }
    else if (m_statement_57(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_statement_57(false, actual, state);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_auto94_59(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual, yaoosl::parsing::instance::if_else_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_94();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l5 = token__auto_94().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_scope_60(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual, yaoosl::parsing::instance::if_else_state& state)
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
bool yaoosl::parsing::instance::m_controlstructure_61(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual, yaoosl::parsing::instance::if_else_state& state)
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
bool yaoosl::parsing::instance::m_statement_62(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual, yaoosl::parsing::instance::if_else_state& state)
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
bool yaoosl::parsing::instance::alternatives63(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual, yaoosl::parsing::instance::if_else_state& state)
{
    resetable resetable1(*this);
    if (m_scope_60(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_scope_60(false, actual, state);
            return true;
        }
    }
    else if (m_controlstructure_61(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_controlstructure_61(false, actual, state);
            return true;
        }
    }
    else if (m_statement_62(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_statement_62(false, actual, state);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::m_auto94_64(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual, yaoosl::parsing::instance::if_else_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_94();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l5 = token__auto_94().value();
    for (;l5 != 0; l5--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::if65_66(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual, yaoosl::parsing::instance::if_else_state& state)
{
    resetable resetable1(*this);
    bool cond2 = m_auto94_64(true, {}, state);
    if (!cond2)
    {
        return false;
    }
    m_auto94_59(false, actual, state);
    alternatives63(false, actual, state);
    return true;
}
bool yaoosl::parsing::instance::p_can_if_else()
{
    resetable resetable1(*this);
    if_else_state state;
    if (!m_auto87_auto7_statement_auto9_54(true, {}, state))
    {
        resetable1.reset();
        return false;
    }
    else if (!alternatives58(true, {}, state))
    {
        resetable1.reset();
        return false;
    }
    else if (!if65_66(true, {}, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::if_else> yaoosl::parsing::instance::p_match_if_else()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::if_else>();
    if_else_state state;
    resetable resetable2(*this);
    if (m_auto87_auto7_statement_auto9_54(true, {}, state))
    {
        resetable2.reset();
        m_auto87_auto7_statement_auto9_54(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    resetable resetable3(*this);
    if (alternatives58(true, {}, state))
    {
        resetable3.reset();
        alternatives58(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    resetable resetable4(*this);
    if (if65_66(true, {}, state))
    {
        resetable4.reset();
        if65_66(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_function_67(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure> actual, yaoosl::parsing::instance::control_structure_state& state)
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
    p_match_function();
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_whileloop_68(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure> actual, yaoosl::parsing::instance::control_structure_state& state)
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
    p_match_while_loop();
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_ifelse_69(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure> actual, yaoosl::parsing::instance::control_structure_state& state)
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
    p_match_if_else();
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_scope_70(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure> actual, yaoosl::parsing::instance::control_structure_state& state)
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
    p_match_scope();
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives71(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure> actual, yaoosl::parsing::instance::control_structure_state& state)
{
    resetable resetable1(*this);
    if (m_function_67(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_function_67(false, actual, state);
            return true;
        }
    }
    else if (m_whileloop_68(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_whileloop_68(false, actual, state);
            return true;
        }
    }
    else if (m_ifelse_69(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_ifelse_69(false, actual, state);
            return true;
        }
    }
    else if (m_scope_70(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_scope_70(false, actual, state);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_control_structure()
{
    resetable resetable1(*this);
    control_structure_state state;
    if (!alternatives71(true, {}, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::control_structure> yaoosl::parsing::instance::p_match_control_structure()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::control_structure>();
    control_structure_state state;
    resetable resetable2(*this);
    if (alternatives71(true, {}, state))
    {
        resetable2.reset();
        alternatives71(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_controlstructure_72(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main> actual, yaoosl::parsing::instance::main_state& state)
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
    p_match_control_structure();
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_statement_73(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main> actual, yaoosl::parsing::instance::main_state& state)
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
    p_match_statement();
    skip();
    return true;
}
bool yaoosl::parsing::instance::alternatives74(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main> actual, yaoosl::parsing::instance::main_state& state)
{
    resetable resetable1(*this);
    if (m_controlstructure_72(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_controlstructure_72(false, actual, state);
            return true;
        }
    }
    else if (m_statement_73(true, {}, state))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_statement_73(false, actual, state);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_main()
{
    resetable resetable1(*this);
    main_state state;
    if (!alternatives74(true, {}, state))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::main> yaoosl::parsing::instance::p_match_main()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::main>();
    main_state state;
    resetable resetable2(*this);
    if (alternatives74(true, {}, state))
    {
        resetable2.reset();
        alternatives74(false, actual, state);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_exparithmetic2_slash_expnullar_75(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state)
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
bool yaoosl::parsing::instance::m_exparithmetic2_star_expnullar_76(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state)
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
bool yaoosl::parsing::instance::m_expnullar_77(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state)
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
    exp_arithmetic_2_state state;
    if (!m_expnullar_77(true, {}, state))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic2_slash_expnullar_75(true, {}, state))
        {
        }
        else if (m_exparithmetic2_star_expnullar_76(true, {}, state))
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
    exp_arithmetic_2_state state;
    if (!m_expnullar_77(false, actual, state))
    {
        report("Something moved wrong (todo: improve error messages)");
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic2_slash_expnullar_75(true, {}, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_2>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic2_slash_expnullar_75(false, actual, state);
        }
        else if (m_exparithmetic2_star_expnullar_76(true, {}, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_2>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic2_star_expnullar_76(false, actual, state);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_exparithmetic1_plus_exparithmetic2_78(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state)
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
bool yaoosl::parsing::instance::m_exparithmetic1_minus_exparithmetic2_79(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state)
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
bool yaoosl::parsing::instance::m_exparithmetic2_80(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state)
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
    exp_arithmetic_1_state state;
    if (!m_exparithmetic2_80(true, {}, state))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic1_plus_exparithmetic2_78(true, {}, state))
        {
        }
        else if (m_exparithmetic1_minus_exparithmetic2_79(true, {}, state))
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
    exp_arithmetic_1_state state;
    if (!m_exparithmetic2_80(false, actual, state))
    {
        report("Something moved wrong (todo: improve error messages)");
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_exparithmetic1_plus_exparithmetic2_78(true, {}, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_1>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic1_plus_exparithmetic2_78(false, actual, state);
        }
        else if (m_exparithmetic1_minus_exparithmetic2_79(true, {}, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_arithmetic_1>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_exparithmetic1_minus_exparithmetic2_79(false, actual, state);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expcompare_auto28_exparithmetic1_81(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare> actual, yaoosl::parsing::instance::exp_compare_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_28();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l5 = token__auto_28().value();
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
bool yaoosl::parsing::instance::m_expcompare_auto31_exparithmetic1_82(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare> actual, yaoosl::parsing::instance::exp_compare_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_31();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l5 = token__auto_31().value();
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
bool yaoosl::parsing::instance::m_expcompare_auto34_exparithmetic1_83(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare> actual, yaoosl::parsing::instance::exp_compare_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_34();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l5 = token__auto_34().value();
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
bool yaoosl::parsing::instance::m_expcompare_auto37_exparithmetic1_84(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare> actual, yaoosl::parsing::instance::exp_compare_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_37();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l5 = token__auto_37().value();
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
bool yaoosl::parsing::instance::m_exparithmetic1_85(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare> actual, yaoosl::parsing::instance::exp_compare_state& state)
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
    exp_compare_state state;
    if (!m_exparithmetic1_85(true, {}, state))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expcompare_auto28_exparithmetic1_81(true, {}, state))
        {
        }
        else if (m_expcompare_auto31_exparithmetic1_82(true, {}, state))
        {
        }
        else if (m_expcompare_auto34_exparithmetic1_83(true, {}, state))
        {
        }
        else if (m_expcompare_auto37_exparithmetic1_84(true, {}, state))
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
    exp_compare_state state;
    if (!m_exparithmetic1_85(false, actual, state))
    {
        report("Something moved wrong (todo: improve error messages)");
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expcompare_auto28_exparithmetic1_81(true, {}, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_auto28_exparithmetic1_81(false, actual, state);
        }
        else if (m_expcompare_auto31_exparithmetic1_82(true, {}, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_auto31_exparithmetic1_82(false, actual, state);
        }
        else if (m_expcompare_auto34_exparithmetic1_83(true, {}, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_auto34_exparithmetic1_83(false, actual, state);
        }
        else if (m_expcompare_auto37_exparithmetic1_84(true, {}, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_compare>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expcompare_auto37_exparithmetic1_84(false, actual, state);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expequality_auto28_expcompare_86(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality> actual, yaoosl::parsing::instance::exp_equality_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_28();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l5 = token__auto_28().value();
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
bool yaoosl::parsing::instance::m_expequality_auto31_expcompare_87(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality> actual, yaoosl::parsing::instance::exp_equality_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_31();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l5 = token__auto_31().value();
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
bool yaoosl::parsing::instance::m_expequality_auto34_expcompare_88(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality> actual, yaoosl::parsing::instance::exp_equality_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_34();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l5 = token__auto_34().value();
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
bool yaoosl::parsing::instance::m_expequality_auto37_expcompare_89(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality> actual, yaoosl::parsing::instance::exp_equality_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_37();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l5 = token__auto_37().value();
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
bool yaoosl::parsing::instance::m_expcompare_90(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality> actual, yaoosl::parsing::instance::exp_equality_state& state)
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
    exp_equality_state state;
    if (!m_expcompare_90(true, {}, state))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expequality_auto28_expcompare_86(true, {}, state))
        {
        }
        else if (m_expequality_auto31_expcompare_87(true, {}, state))
        {
        }
        else if (m_expequality_auto34_expcompare_88(true, {}, state))
        {
        }
        else if (m_expequality_auto37_expcompare_89(true, {}, state))
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
    exp_equality_state state;
    if (!m_expcompare_90(false, actual, state))
    {
        report("Something moved wrong (todo: improve error messages)");
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expequality_auto28_expcompare_86(true, {}, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_auto28_expcompare_86(false, actual, state);
        }
        else if (m_expequality_auto31_expcompare_87(true, {}, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_auto31_expcompare_87(false, actual, state);
        }
        else if (m_expequality_auto34_expcompare_88(true, {}, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_auto34_expcompare_88(false, actual, state);
        }
        else if (m_expequality_auto37_expcompare_89(true, {}, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_equality>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expequality_auto37_expcompare_89(false, actual, state);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expand_auto54_expequality_91(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and> actual, yaoosl::parsing::instance::exp_and_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_54();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l5 = token__auto_54().value();
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
bool yaoosl::parsing::instance::m_expequality_92(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and> actual, yaoosl::parsing::instance::exp_and_state& state)
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
    exp_and_state state;
    if (!m_expequality_92(true, {}, state))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expand_auto54_expequality_91(true, {}, state))
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
    exp_and_state state;
    if (!m_expequality_92(false, actual, state))
    {
        report("Something moved wrong (todo: improve error messages)");
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expand_auto54_expequality_91(true, {}, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_and>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expand_auto54_expequality_91(false, actual, state);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expor_auto58_expequality_93(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or> actual, yaoosl::parsing::instance::exp_or_state& state)
{
    resetable resetable1(*this);
    auto l2 = token__auto_58();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    auto l5 = token__auto_58().value();
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
bool yaoosl::parsing::instance::m_expequality_94(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or> actual, yaoosl::parsing::instance::exp_or_state& state)
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
    exp_or_state state;
    if (!m_expequality_94(true, {}, state))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expor_auto58_expequality_93(true, {}, state))
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
    exp_or_state state;
    if (!m_expequality_94(false, actual, state))
    {
        report("Something moved wrong (todo: improve error messages)");
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expor_auto58_expequality_93(true, {}, state))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::exp_or>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expor_auto58_expequality_93(false, actual, state);
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
    std::cout << "[L" << m_line << "]" << "[C" << m_column << "] " << message;
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
void yaoosl::parsing::instance::print_tree(std::shared_ptr<exp_nullar> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream)
{
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "exp_nullar:\n";
    switch (node->value.index())
    {
        case 0:
        if (std::get<std::shared_ptr<statement>>(node->value))
        {
        }
        else
        {
            goto l000;
        }
        break;
        case 1:
        break;
    }
    v.push_back(3);
    v.push_back(0);
    v.push_back(0);
    switch (node->value.index())
    {
        case 0:
        print_tree(std::get<std::shared_ptr<statement>>(node->value), v, contents, sstream);
        break;
        case 1:
        {
            std::vector<char> copy = v;
            if (!copy.empty())
            {
                bool flag = false;
                for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
                {
                    switch (*it)
                    {
                        case 0: *it = 2; break;
                        case 3:
                        case 1: flag = true; break;
                    }
                }
            }
            for (auto it : copy)
            {
                switch (it)
                {
                    case 0: sstream << ' '; break;
                    case 1: sstream << '|'; break;
                    case 2: sstream << '-'; break;
                    case 3: sstream << '\\'; break;
                }
            }
            for (auto & it : v)
            {
                if (it == 3)
                {
                    it = 0;
                }
            }
        }
        {
            auto tmp = std::get<token>(node->value);
            sstream << "token (L" << tmp.line << "; C" << tmp.column << "; O" << tmp.offset << ") `" << contents.substr(tmp.offset, tmp.length) << "`\n";
        }
        break;
    }
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l000:
}
void yaoosl::parsing::instance::print_tree(std::shared_ptr<exp_assignment> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream)
{
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "exp_assignment:\n";
    if (node->value)
    {
        v.push_back(1);
    }
    else
    {
        v.push_back(3);
    }
    v.push_back(0);
    v.push_back(0);
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    {
        auto tmp = node->name;
        sstream << "token (L" << tmp.line << "; C" << tmp.column << "; O" << tmp.offset << ") `" << contents.substr(tmp.offset, tmp.length) << "`\n";
    }
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l000:
    if (node->value)
    {
    }
    else
    {
        goto l001;
    }
    v.push_back(3);
    v.push_back(0);
    v.push_back(0);
    print_tree(node->value, v, contents, sstream);
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l001:
}
void yaoosl::parsing::instance::print_tree(std::shared_ptr<statement> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream)
{
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "statement:\n";
}
void yaoosl::parsing::instance::print_tree(std::shared_ptr<function_arg> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream)
{
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "function_arg:\n";
    v.push_back(3);
    v.push_back(0);
    v.push_back(0);
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    {
        auto tmp = node->name;
        sstream << "token (L" << tmp.line << "; C" << tmp.column << "; O" << tmp.offset << ") `" << contents.substr(tmp.offset, tmp.length) << "`\n";
    }
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l000:
}
void yaoosl::parsing::instance::print_tree(std::shared_ptr<scope> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream)
{
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "scope:\n";
}
void yaoosl::parsing::instance::print_tree(std::shared_ptr<function> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream)
{
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "function:\n";
    if (node->args)
    {
        v.push_back(1);
    }
    else
    {
        v.push_back(3);
    }
    v.push_back(0);
    v.push_back(0);
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    {
        auto tmp = node->name;
        sstream << "token (L" << tmp.line << "; C" << tmp.column << "; O" << tmp.offset << ") `" << contents.substr(tmp.offset, tmp.length) << "`\n";
    }
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l000:
    if (node->args)
    {
    }
    else
    {
        goto l001;
    }
    if (node->body)
    {
        v.push_back(1);
    }
    else
    {
        v.push_back(3);
    }
    v.push_back(0);
    v.push_back(0);
    print_tree(node->args, v, contents, sstream);
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l001:
    if (node->body)
    {
    }
    else
    {
        goto l002;
    }
    v.push_back(3);
    v.push_back(0);
    v.push_back(0);
    print_tree(node->body, v, contents, sstream);
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l002:
}
void yaoosl::parsing::instance::print_tree(std::shared_ptr<while_loop> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream)
{
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "while_loop:\n";
    if (node->condition)
    {
    }
    else
    {
        goto l000;
    }
    if (node->body)
    {
        v.push_back(1);
    }
    else
    {
        v.push_back(3);
    }
    v.push_back(0);
    v.push_back(0);
    print_tree(node->condition, v, contents, sstream);
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l000:
    if (node->body)
    {
    }
    else
    {
        goto l001;
    }
    v.push_back(3);
    v.push_back(0);
    v.push_back(0);
    print_tree(node->body, v, contents, sstream);
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l001:
}
void yaoosl::parsing::instance::print_tree(std::shared_ptr<if_else> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream)
{
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "if_else:\n";
    if (node->condition)
    {
    }
    else
    {
        goto l000;
    }
    switch (node->if_body.index())
    {
        case 0:
        if (std::get<std::shared_ptr<scope>>(node->if_body))
        {
            v.push_back(1);
        }
        else
        {
            v.push_back(3);
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<control_structure>>(node->if_body))
        {
            v.push_back(1);
        }
        else
        {
            v.push_back(3);
        }
        break;
        case 2:
        if (std::get<std::shared_ptr<statement>>(node->if_body))
        {
            v.push_back(1);
        }
        else
        {
            v.push_back(3);
        }
        break;
    }
    v.push_back(0);
    v.push_back(0);
    print_tree(node->condition, v, contents, sstream);
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l000:
    switch (node->if_body.index())
    {
        case 0:
        if (std::get<std::shared_ptr<scope>>(node->if_body))
        {
        }
        else
        {
            goto l001;
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<control_structure>>(node->if_body))
        {
        }
        else
        {
            goto l001;
        }
        break;
        case 2:
        if (std::get<std::shared_ptr<statement>>(node->if_body))
        {
        }
        else
        {
            goto l001;
        }
        break;
    }
    switch (node->else_body.index())
    {
        case 0:
        if (std::get<std::shared_ptr<scope>>(node->else_body))
        {
            v.push_back(1);
        }
        else
        {
            v.push_back(3);
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<control_structure>>(node->else_body))
        {
            v.push_back(1);
        }
        else
        {
            v.push_back(3);
        }
        break;
        case 2:
        if (std::get<std::shared_ptr<statement>>(node->else_body))
        {
            v.push_back(1);
        }
        else
        {
            v.push_back(3);
        }
        break;
    }
    v.push_back(0);
    v.push_back(0);
    switch (node->if_body.index())
    {
        case 0:
        print_tree(std::get<std::shared_ptr<scope>>(node->if_body), v, contents, sstream);
        break;
        case 1:
        print_tree(std::get<std::shared_ptr<control_structure>>(node->if_body), v, contents, sstream);
        break;
        case 2:
        print_tree(std::get<std::shared_ptr<statement>>(node->if_body), v, contents, sstream);
        break;
    }
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l001:
    switch (node->else_body.index())
    {
        case 0:
        if (std::get<std::shared_ptr<scope>>(node->else_body))
        {
        }
        else
        {
            goto l002;
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<control_structure>>(node->else_body))
        {
        }
        else
        {
            goto l002;
        }
        break;
        case 2:
        if (std::get<std::shared_ptr<statement>>(node->else_body))
        {
        }
        else
        {
            goto l002;
        }
        break;
    }
    v.push_back(3);
    v.push_back(0);
    v.push_back(0);
    switch (node->else_body.index())
    {
        case 0:
        print_tree(std::get<std::shared_ptr<scope>>(node->else_body), v, contents, sstream);
        break;
        case 1:
        print_tree(std::get<std::shared_ptr<control_structure>>(node->else_body), v, contents, sstream);
        break;
        case 2:
        print_tree(std::get<std::shared_ptr<statement>>(node->else_body), v, contents, sstream);
        break;
    }
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l002:
}
void yaoosl::parsing::instance::print_tree(std::shared_ptr<control_structure> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream)
{
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "control_structure:\n";
}
void yaoosl::parsing::instance::print_tree(std::shared_ptr<main> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream)
{
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "main:\n";
}
void yaoosl::parsing::instance::print_tree(std::shared_ptr<exp_arithmetic_2> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream)
{
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "exp_arithmetic_2:\n";
    if (node->op.has_value())
    {
    }
    else
    {
        goto l000;
    }
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_arithmetic_2>>(node->left))
        {
            v.push_back(1);
        }
        else
        {
            v.push_back(3);
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_nullar>>(node->left))
        {
            v.push_back(1);
        }
        else
        {
            v.push_back(3);
        }
        break;
    }
    v.push_back(0);
    v.push_back(0);
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "`" << node->op.value() << "`\n";
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l000:
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_arithmetic_2>>(node->left))
        {
        }
        else
        {
            goto l001;
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_nullar>>(node->left))
        {
        }
        else
        {
            goto l001;
        }
        break;
    }
    if (node->right)
    {
        v.push_back(1);
    }
    else
    {
        v.push_back(3);
    }
    v.push_back(0);
    v.push_back(0);
    switch (node->left.index())
    {
        case 0:
        print_tree(std::get<std::shared_ptr<exp_arithmetic_2>>(node->left), v, contents, sstream);
        break;
        case 1:
        print_tree(std::get<std::shared_ptr<exp_nullar>>(node->left), v, contents, sstream);
        break;
    }
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l001:
    if (node->right)
    {
    }
    else
    {
        goto l002;
    }
    v.push_back(3);
    v.push_back(0);
    v.push_back(0);
    print_tree(node->right, v, contents, sstream);
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l002:
}
void yaoosl::parsing::instance::print_tree(std::shared_ptr<exp_arithmetic_1> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream)
{
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "exp_arithmetic_1:\n";
    if (node->op.has_value())
    {
    }
    else
    {
        goto l000;
    }
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_arithmetic_1>>(node->left))
        {
            v.push_back(1);
        }
        else
        {
            v.push_back(3);
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_arithmetic_2>>(node->left))
        {
            v.push_back(1);
        }
        else
        {
            v.push_back(3);
        }
        break;
    }
    v.push_back(0);
    v.push_back(0);
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "`" << node->op.value() << "`\n";
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l000:
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_arithmetic_1>>(node->left))
        {
        }
        else
        {
            goto l001;
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_arithmetic_2>>(node->left))
        {
        }
        else
        {
            goto l001;
        }
        break;
    }
    if (node->right)
    {
        v.push_back(1);
    }
    else
    {
        v.push_back(3);
    }
    v.push_back(0);
    v.push_back(0);
    switch (node->left.index())
    {
        case 0:
        print_tree(std::get<std::shared_ptr<exp_arithmetic_1>>(node->left), v, contents, sstream);
        break;
        case 1:
        print_tree(std::get<std::shared_ptr<exp_arithmetic_2>>(node->left), v, contents, sstream);
        break;
    }
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l001:
    if (node->right)
    {
    }
    else
    {
        goto l002;
    }
    v.push_back(3);
    v.push_back(0);
    v.push_back(0);
    print_tree(node->right, v, contents, sstream);
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l002:
}
void yaoosl::parsing::instance::print_tree(std::shared_ptr<exp_compare> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream)
{
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "exp_compare:\n";
    if (node->op1.has_value())
    {
    }
    else
    {
        goto l000;
    }
    if (node->eq2.has_value())
    {
        v.push_back(1);
    }
    else
    {
        v.push_back(3);
    }
    v.push_back(0);
    v.push_back(0);
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "`" << node->op1.value() << "`\n";
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l000:
    if (node->eq2.has_value())
    {
    }
    else
    {
        goto l001;
    }
    if (node->op2.has_value())
    {
        v.push_back(1);
    }
    else
    {
        v.push_back(3);
    }
    v.push_back(0);
    v.push_back(0);
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "`" << node->eq2.value() << "`\n";
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l001:
    if (node->op2.has_value())
    {
    }
    else
    {
        goto l002;
    }
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_compare>>(node->left))
        {
            v.push_back(1);
        }
        else
        {
            v.push_back(3);
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_arithmetic_1>>(node->left))
        {
            v.push_back(1);
        }
        else
        {
            v.push_back(3);
        }
        break;
    }
    v.push_back(0);
    v.push_back(0);
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "`" << node->op2.value() << "`\n";
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l002:
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_compare>>(node->left))
        {
        }
        else
        {
            goto l003;
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_arithmetic_1>>(node->left))
        {
        }
        else
        {
            goto l003;
        }
        break;
    }
    if (node->right)
    {
        v.push_back(1);
    }
    else
    {
        v.push_back(3);
    }
    v.push_back(0);
    v.push_back(0);
    switch (node->left.index())
    {
        case 0:
        print_tree(std::get<std::shared_ptr<exp_compare>>(node->left), v, contents, sstream);
        break;
        case 1:
        print_tree(std::get<std::shared_ptr<exp_arithmetic_1>>(node->left), v, contents, sstream);
        break;
    }
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l003:
    if (node->right)
    {
    }
    else
    {
        goto l004;
    }
    v.push_back(3);
    v.push_back(0);
    v.push_back(0);
    print_tree(node->right, v, contents, sstream);
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l004:
}
void yaoosl::parsing::instance::print_tree(std::shared_ptr<exp_equality> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream)
{
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "exp_equality:\n";
    if (node->op1.has_value())
    {
    }
    else
    {
        goto l000;
    }
    if (node->eq2.has_value())
    {
        v.push_back(1);
    }
    else
    {
        v.push_back(3);
    }
    v.push_back(0);
    v.push_back(0);
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "`" << node->op1.value() << "`\n";
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l000:
    if (node->eq2.has_value())
    {
    }
    else
    {
        goto l001;
    }
    if (node->op2.has_value())
    {
        v.push_back(1);
    }
    else
    {
        v.push_back(3);
    }
    v.push_back(0);
    v.push_back(0);
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "`" << node->eq2.value() << "`\n";
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l001:
    if (node->op2.has_value())
    {
    }
    else
    {
        goto l002;
    }
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_equality>>(node->left))
        {
            v.push_back(1);
        }
        else
        {
            v.push_back(3);
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_compare>>(node->left))
        {
            v.push_back(1);
        }
        else
        {
            v.push_back(3);
        }
        break;
    }
    v.push_back(0);
    v.push_back(0);
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "`" << node->op2.value() << "`\n";
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l002:
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_equality>>(node->left))
        {
        }
        else
        {
            goto l003;
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_compare>>(node->left))
        {
        }
        else
        {
            goto l003;
        }
        break;
    }
    if (node->right)
    {
        v.push_back(1);
    }
    else
    {
        v.push_back(3);
    }
    v.push_back(0);
    v.push_back(0);
    switch (node->left.index())
    {
        case 0:
        print_tree(std::get<std::shared_ptr<exp_equality>>(node->left), v, contents, sstream);
        break;
        case 1:
        print_tree(std::get<std::shared_ptr<exp_compare>>(node->left), v, contents, sstream);
        break;
    }
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l003:
    if (node->right)
    {
    }
    else
    {
        goto l004;
    }
    v.push_back(3);
    v.push_back(0);
    v.push_back(0);
    print_tree(node->right, v, contents, sstream);
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l004:
}
void yaoosl::parsing::instance::print_tree(std::shared_ptr<exp_and> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream)
{
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "exp_and:\n";
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_and>>(node->left))
        {
        }
        else
        {
            goto l000;
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_equality>>(node->left))
        {
        }
        else
        {
            goto l000;
        }
        break;
    }
    if (node->right)
    {
        v.push_back(1);
    }
    else
    {
        v.push_back(3);
    }
    v.push_back(0);
    v.push_back(0);
    switch (node->left.index())
    {
        case 0:
        print_tree(std::get<std::shared_ptr<exp_and>>(node->left), v, contents, sstream);
        break;
        case 1:
        print_tree(std::get<std::shared_ptr<exp_equality>>(node->left), v, contents, sstream);
        break;
    }
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l000:
    if (node->right)
    {
    }
    else
    {
        goto l001;
    }
    v.push_back(3);
    v.push_back(0);
    v.push_back(0);
    print_tree(node->right, v, contents, sstream);
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l001:
}
void yaoosl::parsing::instance::print_tree(std::shared_ptr<exp_or> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream)
{
    {
        std::vector<char> copy = v;
        if (!copy.empty())
        {
            bool flag = false;
            for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)
            {
                switch (*it)
                {
                    case 0: *it = 2; break;
                    case 3:
                    case 1: flag = true; break;
                }
            }
        }
        for (auto it : copy)
        {
            switch (it)
            {
                case 0: sstream << ' '; break;
                case 1: sstream << '|'; break;
                case 2: sstream << '-'; break;
                case 3: sstream << '\\'; break;
            }
        }
        for (auto & it : v)
        {
            if (it == 3)
            {
                it = 0;
            }
        }
    }
    sstream << "exp_or:\n";
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<exp_or>>(node->left))
        {
        }
        else
        {
            goto l000;
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<exp_equality>>(node->left))
        {
        }
        else
        {
            goto l000;
        }
        break;
    }
    if (node->right)
    {
        v.push_back(1);
    }
    else
    {
        v.push_back(3);
    }
    v.push_back(0);
    v.push_back(0);
    switch (node->left.index())
    {
        case 0:
        print_tree(std::get<std::shared_ptr<exp_or>>(node->left), v, contents, sstream);
        break;
        case 1:
        print_tree(std::get<std::shared_ptr<exp_equality>>(node->left), v, contents, sstream);
        break;
    }
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l000:
    if (node->right)
    {
    }
    else
    {
        goto l001;
    }
    v.push_back(3);
    v.push_back(0);
    v.push_back(0);
    print_tree(node->right, v, contents, sstream);
    v.pop_back();
    v.pop_back();
    v.pop_back();
    l001:
}
std::shared_ptr<yaoosl::parsing::instance::main> yaoosl::parsing::instance::parse()
{
    return p_match_main();
}
