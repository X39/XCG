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
            resetable1.reset();
            return {};
        }
    }
    auto resultVariable2 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable2;
}
std::optional<size_t> yaoosl::parsing::instance::token_scalar()
{
    resetable resetable3(*this);
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
            resetable3.reset();
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
            resetable3.reset();
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
            resetable3.reset();
            return {};
        }
    }
    auto resultVariable4 = m_offset - resetable3.m_offset;
    resetable3.reset();
    return resultVariable4;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_3()
{
    resetable resetable5(*this);
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
            resetable5.reset();
            return {};
        }
    }
    auto resultVariable6 = m_offset - resetable5.m_offset;
    resetable5.reset();
    return resultVariable6;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_5()
{
    resetable resetable7(*this);
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
            resetable7.reset();
            return {};
        }
    }
    auto resultVariable8 = m_offset - resetable7.m_offset;
    resetable7.reset();
    return resultVariable8;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_9()
{
    resetable resetable9(*this);
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
            resetable9.reset();
            return {};
        }
    }
    auto resultVariable10 = m_offset - resetable9.m_offset;
    resetable9.reset();
    return resultVariable10;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_12()
{
    resetable resetable11(*this);
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
            resetable11.reset();
            return {};
        }
    }
    auto resultVariable12 = m_offset - resetable11.m_offset;
    resetable11.reset();
    return resultVariable12;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_16()
{
    resetable resetable13(*this);
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
            resetable13.reset();
            return {};
        }
    }
    auto resultVariable14 = m_offset - resetable13.m_offset;
    resetable13.reset();
    return resultVariable14;
}
std::optional<size_t> yaoosl::parsing::instance::token__auto_19()
{
    resetable resetable15(*this);
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
            resetable15.reset();
            return {};
        }
    }
    auto resultVariable16 = m_offset - resetable15.m_offset;
    resetable15.reset();
    return resultVariable16;
}
bool yaoosl::parsing::instance::auto3_expA_auto5_18(bool is_can, std::shared_ptr<yaoosl::parsing::instance::p_expc> actual)
{
    resetable resetable17(*this);
    if (token__auto_3().has_value() && lr_can_expa() && token__auto_5().has_value())
    {
        if (!is_can)
        {
            resetable17.reset();
            token__auto_3();
            auto val20 = lr_match_expa();
            actual->value = val20;
            token__auto_5();
        }
        return true;
    }
    else if (is_can)
    {
        resetable17.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
}
bool yaoosl::parsing::instance::scalar_23(bool is_can, std::shared_ptr<yaoosl::parsing::instance::p_expc> actual)
{
    resetable resetable22(*this);
    if (token_scalar().has_value())
    {
        if (!is_can)
        {
            resetable22.reset();
            auto val24 = create_token(token_scalar().value(), tok::SCALAR);
            actual->value = val24;
        }
        return true;
    }
    else if (is_can)
    {
        resetable22.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
}
bool yaoosl::parsing::instance::integer_26(bool is_can, std::shared_ptr<yaoosl::parsing::instance::p_expc> actual)
{
    resetable resetable25(*this);
    if (token_integer().has_value())
    {
        if (!is_can)
        {
            resetable25.reset();
            auto val27 = create_token(token_integer().value(), tok::INTEGER);
            actual->value = val27;
        }
        return true;
    }
    else if (is_can)
    {
        resetable25.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
}
bool yaoosl::parsing::instance::alternatives28(bool is_can, std::shared_ptr<yaoosl::parsing::instance::p_expc> actual)
{
    resetable resetable29(*this);
    if (auto3_expA_auto5_18(true, {}))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            auto3_expA_auto5_18(false, actual);
            return true;
        }
    }
    else if (scalar_23(true, {}))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            scalar_23(false, actual);
            return true;
        }
    }
    else if (integer_26(true, {}))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            integer_26(false, actual);
            return true;
        }
    }
    resetable29.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_expc()
{
    resetable resetable30(*this);
    if (!alternatives28(true, {}))
    {
        resetable30.reset();
        return false;
    }
    resetable30.reset();
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::p_expc> yaoosl::parsing::instance::p_match_expc()
{
    resetable resetable30(*this);
    auto actual = std::make_shared<yaoosl::parsing::instance::p_expc>();
    if (alternatives28(true, {}))
    {
        alternatives28(false, actual);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::expA_32(bool is_can, std::shared_ptr<yaoosl::parsing::instance::p_main> actual)
{
    resetable resetable31(*this);
    if (lr_can_expa())
    {
        if (!is_can)
        {
            resetable31.reset();
            auto val33 = lr_match_expa();
            actual->root = val33;
        }
        return true;
    }
    else if (is_can)
    {
        resetable31.reset();
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
    resetable resetable34(*this);
    if (!expA_32(true, {}))
    {
        resetable34.reset();
        return false;
    }
    resetable34.reset();
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::p_main> yaoosl::parsing::instance::p_match_main()
{
    resetable resetable34(*this);
    auto actual = std::make_shared<yaoosl::parsing::instance::p_main>();
    if (expA_32(true, {}))
    {
        expA_32(false, actual);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::expB_auto9_expC_36(bool is_can, std::shared_ptr<yaoosl::parsing::instance::lr_expb> actual)
{
    resetable resetable35(*this);
    if (lr_can_expb() && token__auto_9().has_value() && p_can_expc())
    {
        if (!is_can)
        {
            resetable35.reset();
            auto val37 = lr_match_expb();
            actual->left = val37;
            token__auto_9();
            auto val39 = p_match_expc();
            actual->right = val39;
        }
        if (!is_can)
        {
            actual->op = '/';
        }
        return true;
    }
    else if (is_can)
    {
        resetable35.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
}
bool yaoosl::parsing::instance::expB_auto12_expC_41(bool is_can, std::shared_ptr<yaoosl::parsing::instance::lr_expb> actual)
{
    resetable resetable40(*this);
    if (lr_can_expb() && token__auto_12().has_value() && p_can_expc())
    {
        if (!is_can)
        {
            resetable40.reset();
            auto val42 = lr_match_expb();
            actual->left = val42;
            token__auto_12();
            auto val44 = p_match_expc();
            actual->right = val44;
        }
        if (!is_can)
        {
            actual->op = '*';
        }
        return true;
    }
    else if (is_can)
    {
        resetable40.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
}
bool yaoosl::parsing::instance::expC_46(bool is_can, std::shared_ptr<yaoosl::parsing::instance::lr_expb> actual)
{
    resetable resetable45(*this);
    if (p_can_expc())
    {
        if (!is_can)
        {
            resetable45.reset();
            auto val47 = p_match_expc();
            actual->left = val47;
        }
        return true;
    }
    else if (is_can)
    {
        resetable45.reset();
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
    resetable resetable48(*this);
    if (expC_46(true, {}))
    {
        resetable48.reset();
        return true;
    }
    return false;
}
std::shared_ptr<yaoosl::parsing::instance::lr_expb> yaoosl::parsing::instance::lr_match_expb()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::lr_expb>();
    expC_46(false, actual);
    while (true)
    {
        if (expB_auto9_expC_36(true, {}))
        {
            expB_auto9_expC_36(false, actual);
        }
        else if (expB_auto12_expC_41(true, {}))
        {
            expB_auto12_expC_41(false, actual);
        }
        else
        {
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::expA_auto16_expB_50(bool is_can, std::shared_ptr<yaoosl::parsing::instance::lr_expa> actual)
{
    resetable resetable49(*this);
    if (lr_can_expa() && token__auto_16().has_value() && lr_can_expb())
    {
        if (!is_can)
        {
            resetable49.reset();
            auto val51 = lr_match_expa();
            actual->left = val51;
            token__auto_16();
            auto val53 = lr_match_expb();
            actual->right = val53;
        }
        if (!is_can)
        {
            actual->op = '+';
        }
        return true;
    }
    else if (is_can)
    {
        resetable49.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
}
bool yaoosl::parsing::instance::expA_auto19_expB_55(bool is_can, std::shared_ptr<yaoosl::parsing::instance::lr_expa> actual)
{
    resetable resetable54(*this);
    if (lr_can_expa() && token__auto_19().has_value() && lr_can_expb())
    {
        if (!is_can)
        {
            resetable54.reset();
            auto val56 = lr_match_expa();
            actual->left = val56;
            token__auto_19();
            auto val58 = lr_match_expb();
            actual->right = val58;
        }
        if (!is_can)
        {
            actual->op = '-';
        }
        return true;
    }
    else if (is_can)
    {
        resetable54.reset();
        return false;
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
        return false;
    }
}
bool yaoosl::parsing::instance::expB_60(bool is_can, std::shared_ptr<yaoosl::parsing::instance::lr_expa> actual)
{
    resetable resetable59(*this);
    if (lr_can_expb())
    {
        if (!is_can)
        {
            resetable59.reset();
            auto val61 = lr_match_expb();
            actual->left = val61;
        }
        return true;
    }
    else if (is_can)
    {
        resetable59.reset();
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
    resetable resetable62(*this);
    if (expB_60(true, {}))
    {
        resetable62.reset();
        return true;
    }
    return false;
}
std::shared_ptr<yaoosl::parsing::instance::lr_expa> yaoosl::parsing::instance::lr_match_expa()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::lr_expa>();
    expB_60(false, actual);
    while (true)
    {
        if (expA_auto16_expB_50(true, {}))
        {
            expA_auto16_expB_50(false, actual);
        }
        else if (expA_auto19_expB_55(true, {}))
        {
            expA_auto19_expB_55(false, actual);
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
yaoosl::parsing::instance::token yaoosl::parsing::instance::create_token(size_t length, tok type)
{
    token t;
    t.file = m_file;
    t.line = m_line;
    t.column = m_column;
    t.offset = m_offset;
    t.length = length;
    t.type = type;
    return t;
}
std::shared_ptr<yaoosl::parsing::instance::p_main> yaoosl::parsing::instance::parse()
{
    return p_match_main();
}
