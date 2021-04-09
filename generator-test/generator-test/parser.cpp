#include "parser.hpp"
#include <iostream>

yaoosl::parsing::instance::resetable::resetable(instance& ref) : m_ref(ref)
{
    m_contents = ref.m_contents;
    m_file = ref.m_file;
    m_line = ref.m_line;
    m_column = ref.m_column;
    m_offset = ref.m_offset;
}
void yaoosl::parsing::instance::resetable::reset()
{
    m_ref.m_contents = m_contents;
    m_ref.m_file = m_file;
    m_ref.m_line = m_line;
    m_ref.m_column = m_column;
    m_ref.m_offset = m_offset;
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
            case ' ': m_column++; m_offset++; break;
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
    auto r = resetable(*this);
    {
        size_t count = 0;
        while (current() != '\0')
        {
            if ('0' <= current() && current() <= '9')
            {
                count++;
                next();
                continue;
            }
            break;
        }
        if (count < 1)
        {
            r.reset();
            return {};
        }
    }
    return {};
}
std::optional<size_t> yaoosl::parsing::instance::token_scalar()
{
    auto r = resetable(*this);
    {
        size_t count = 0;
        while (current() != '\0' && count < 1)
        {
            auto l1 = token_integer();
            if (l1.has_value())
            {
                count++;
                for (size_t i = 0; i < l1; i++)
                {
                    next();
                }
                continue;
            }
            break;
        }
        if (count < 1)
        {
            r.reset();
            return {};
        }
    }
    {
        size_t count = 0;
        while (current() != '\0' && count < 1)
        {
            if (current() == '.')
            {
                count++;
                next();
                continue;
            }
            break;
        }
        if (count < 1)
        {
            r.reset();
            return {};
        }
    }
    {
        size_t count = 0;
        while (current() != '\0' && count < 1)
        {
            auto l1 = token_integer();
            if (l1.has_value())
            {
                count++;
                for (size_t i = 0; i < l1; i++)
                {
                    next();
                }
                continue;
            }
            break;
        }
        if (count < 1)
        {
            r.reset();
            return {};
        }
    }
    return {};
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_3()
{
    auto r = resetable(*this);
    {
        size_t count = 0;
        while (current() != '\0' && count < 1)
        {
            if (current() == '(')
            {
                count++;
                next();
                continue;
            }
            break;
        }
        if (count < 1)
        {
            r.reset();
            return {};
        }
    }
    return {};
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_5()
{
    auto r = resetable(*this);
    {
        size_t count = 0;
        while (current() != '\0' && count < 1)
        {
            if (current() == ')')
            {
                count++;
                next();
                continue;
            }
            break;
        }
        if (count < 1)
        {
            r.reset();
            return {};
        }
    }
    return {};
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_9()
{
    auto r = resetable(*this);
    {
        size_t count = 0;
        while (current() != '\0' && count < 1)
        {
            if (current() == '/')
            {
                count++;
                next();
                continue;
            }
            break;
        }
        if (count < 1)
        {
            r.reset();
            return {};
        }
    }
    return {};
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_12()
{
    auto r = resetable(*this);
    {
        size_t count = 0;
        while (current() != '\0' && count < 1)
        {
            if (current() == '*')
            {
                count++;
                next();
                continue;
            }
            break;
        }
        if (count < 1)
        {
            r.reset();
            return {};
        }
    }
    return {};
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_16()
{
    auto r = resetable(*this);
    {
        size_t count = 0;
        while (current() != '\0' && count < 1)
        {
            if (current() == '+')
            {
                count++;
                next();
                continue;
            }
            break;
        }
        if (count < 1)
        {
            r.reset();
            return {};
        }
    }
    return {};
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_19()
{
    auto r = resetable(*this);
    {
        size_t count = 0;
        while (current() != '\0' && count < 1)
        {
            if (current() == '-')
            {
                count++;
                next();
                continue;
            }
            break;
        }
        if (count < 1)
        {
            r.reset();
            return {};
        }
    }
    return {};
}
bool yaoosl::parsing::instance::match2(bool is_can, std::shared_ptr<yaoosl::parsing::instance::p_expc> actual)
{
    resetable resetable1(*this);
    if (token__auto_3().has_value() && lr_can_expa() && token__auto_5().has_value())
    {
        if (!is_can)
        {
            resetable1.reset();
            token__auto_3();
            auto val4 = lr_match_expa();
            actual->value = val4;
            token__auto_5();
        }
        return true;
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
}
bool yaoosl::parsing::instance::match7(bool is_can, std::shared_ptr<yaoosl::parsing::instance::p_expc> actual)
{
    resetable resetable6(*this);
    if (token_scalar().has_value())
    {
        if (!is_can)
        {
            resetable6.reset();
            auto val8 = create_token(token_scalar().value());
            actual->value = val8;
        }
        return true;
    }
    else if (is_can)
    {
        resetable6.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
}
bool yaoosl::parsing::instance::match10(bool is_can, std::shared_ptr<yaoosl::parsing::instance::p_expc> actual)
{
    resetable resetable9(*this);
    if (token_integer().has_value())
    {
        if (!is_can)
        {
            resetable9.reset();
            auto val11 = create_token(token_integer().value());
            actual->value = val11;
        }
        return true;
    }
    else if (is_can)
    {
        resetable9.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
}
bool yaoosl::parsing::instance::alternatives12(bool is_can, std::shared_ptr<yaoosl::parsing::instance::p_expc> actual)
{
    resetable resetable13(*this);
    if (match2(true, {}))
    {
        if (is_can)
        {
            match2(true, actual);
        }
        else
        {
            return true;
        }
    }
    else if (match7(true, {}))
    {
        if (is_can)
        {
            match7(true, actual);
        }
        else
        {
            return true;
        }
    }
    else if (match10(true, {}))
    {
        if (is_can)
        {
            match10(true, actual);
        }
        else
        {
            return true;
        }
    }
    resetable13.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_expc()
{
    resetable resetable14(*this);
    if (!alternatives12(true, {}))
    {
        resetable14.reset();
        return false;
    }
    resetable14.reset();
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::p_expc> yaoosl::parsing::instance::p_match_expc()
{
    resetable resetable14(*this);
    auto actual = std::make_shared<yaoosl::parsing::instance::p_expc>();
    if (alternatives12(true, {}))
    {
        alternatives12(false, actual);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::match16(bool is_can, std::shared_ptr<yaoosl::parsing::instance::p_main> actual)
{
    resetable resetable15(*this);
    if (lr_can_expa())
    {
        if (!is_can)
        {
            resetable15.reset();
            auto val17 = lr_match_expa();
            actual->root = val17;
        }
        return true;
    }
    else if (is_can)
    {
        resetable15.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
}
bool yaoosl::parsing::instance::p_can_main()
{
    resetable resetable18(*this);
    if (!match16(true, {}))
    {
        resetable18.reset();
        return false;
    }
    resetable18.reset();
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::p_main> yaoosl::parsing::instance::p_match_main()
{
    resetable resetable18(*this);
    auto actual = std::make_shared<yaoosl::parsing::instance::p_main>();
    if (match16(true, {}))
    {
        match16(false, actual);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::match20(bool is_can, std::shared_ptr<yaoosl::parsing::instance::lr_expb> actual)
{
    resetable resetable19(*this);
    if (lr_can_expb() && token__auto_9().has_value() && p_can_expc())
    {
        if (!is_can)
        {
            resetable19.reset();
            auto val21 = lr_match_expb();
            actual->left = val21;
            token__auto_9();
            auto val23 = p_match_expc();
            actual->right = val23;
        }
        if (!is_can)
        {
            actual->op = '/';
        }
        return true;
    }
    else if (is_can)
    {
        resetable19.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
}
bool yaoosl::parsing::instance::match25(bool is_can, std::shared_ptr<yaoosl::parsing::instance::lr_expb> actual)
{
    resetable resetable24(*this);
    if (lr_can_expb() && token__auto_12().has_value() && p_can_expc())
    {
        if (!is_can)
        {
            resetable24.reset();
            auto val26 = lr_match_expb();
            actual->left = val26;
            token__auto_12();
            auto val28 = p_match_expc();
            actual->right = val28;
        }
        if (!is_can)
        {
            actual->op = '*';
        }
        return true;
    }
    else if (is_can)
    {
        resetable24.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
}
bool yaoosl::parsing::instance::match30(bool is_can, std::shared_ptr<yaoosl::parsing::instance::lr_expb> actual)
{
    resetable resetable29(*this);
    if (p_can_expc())
    {
        if (!is_can)
        {
            resetable29.reset();
            auto val31 = p_match_expc();
            actual->left = val31;
        }
        return true;
    }
    else if (is_can)
    {
        resetable29.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
}
bool yaoosl::parsing::instance::lr_can_expb()
{
    resetable resetable32(*this);
    if (match30(true, {}))
    {
        resetable32.reset();
        return true;
    }
    return false;
}
std::shared_ptr<yaoosl::parsing::instance::lr_expb> yaoosl::parsing::instance::lr_match_expb()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::lr_expb>();
    match30(false, actual);
    while (true)
    {
        if (match20(true, {}))
        {
            match20(false, actual);
        }
        else if (match25(true, {}))
        {
            match25(false, actual);
        }
        else
        {
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::match34(bool is_can, std::shared_ptr<yaoosl::parsing::instance::lr_expa> actual)
{
    resetable resetable33(*this);
    if (lr_can_expa() && token__auto_16().has_value() && lr_can_expb())
    {
        if (!is_can)
        {
            resetable33.reset();
            auto val35 = lr_match_expa();
            actual->left = val35;
            token__auto_16();
            auto val37 = lr_match_expb();
            actual->right = val37;
        }
        if (!is_can)
        {
            actual->op = '+';
        }
        return true;
    }
    else if (is_can)
    {
        resetable33.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
}
bool yaoosl::parsing::instance::match39(bool is_can, std::shared_ptr<yaoosl::parsing::instance::lr_expa> actual)
{
    resetable resetable38(*this);
    if (lr_can_expa() && token__auto_19().has_value() && lr_can_expb())
    {
        if (!is_can)
        {
            resetable38.reset();
            auto val40 = lr_match_expa();
            actual->left = val40;
            token__auto_19();
            auto val42 = lr_match_expb();
            actual->right = val42;
        }
        if (!is_can)
        {
            actual->op = '-';
        }
        return true;
    }
    else if (is_can)
    {
        resetable38.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
}
bool yaoosl::parsing::instance::match44(bool is_can, std::shared_ptr<yaoosl::parsing::instance::lr_expa> actual)
{
    resetable resetable43(*this);
    if (lr_can_expb())
    {
        if (!is_can)
        {
            resetable43.reset();
            auto val45 = lr_match_expb();
            actual->left = val45;
        }
        return true;
    }
    else if (is_can)
    {
        resetable43.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
}
bool yaoosl::parsing::instance::lr_can_expa()
{
    resetable resetable46(*this);
    if (match44(true, {}))
    {
        resetable46.reset();
        return true;
    }
    return false;
}
std::shared_ptr<yaoosl::parsing::instance::lr_expa> yaoosl::parsing::instance::lr_match_expa()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::lr_expa>();
    match44(false, actual);
    while (true)
    {
        if (match34(true, {}))
        {
            match34(false, actual);
        }
        else if (match39(true, {}))
        {
            match39(false, actual);
        }
        else
        {
            break;
        }
    }
    return actual;
}
void yaoosl::parsing::instance::report(std::string_view message)
{
    std::cout << "[L" << m_line << "]" << "[C" << m_column << "] " << message;
}
yaoosl::parsing::instance::token yaoosl::parsing::instance::create_token(size_t length)
{
    token t;
    t.file = m_file;
    t.line = m_line;
    t.column = m_column;
    t.offset = m_offset;
    t.length = length;
    return t;
}
