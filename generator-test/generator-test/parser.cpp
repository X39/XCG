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
    auto resultVariable1 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable1;
}
std::optional<size_t> yaoosl::parsing::instance::token_scalar()
{
    resetable resetable1(*this);
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
            resetable1.reset();
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
            resetable1.reset();
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
            resetable1.reset();
            return {};
        }
    }
    auto resultVariable2 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable2;
}
std::optional<size_t> yaoosl::parsing::instance::token_roundo()
{
    resetable resetable1(*this);
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
            resetable1.reset();
            return {};
        }
    }
    auto resultVariable3 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable3;
}
std::optional<size_t> yaoosl::parsing::instance::token_roundc()
{
    resetable resetable1(*this);
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
            resetable1.reset();
            return {};
        }
    }
    auto resultVariable4 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable4;
}
std::optional<size_t> yaoosl::parsing::instance::token_slash()
{
    resetable resetable1(*this);
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
            resetable1.reset();
            return {};
        }
    }
    auto resultVariable5 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable5;
}
std::optional<size_t> yaoosl::parsing::instance::token_star()
{
    resetable resetable1(*this);
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
            resetable1.reset();
            return {};
        }
    }
    auto resultVariable6 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable6;
}
std::optional<size_t> yaoosl::parsing::instance::token_plus()
{
    resetable resetable1(*this);
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
            resetable1.reset();
            return {};
        }
    }
    auto resultVariable7 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable7;
}
std::optional<size_t> yaoosl::parsing::instance::token_minus()
{
    resetable resetable1(*this);
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
            resetable1.reset();
            return {};
        }
    }
    auto resultVariable8 = m_offset - resetable1.m_offset;
    resetable1.reset();
    return resultVariable8;
}
bool yaoosl::parsing::instance::m_roundO_expA_roundC_9(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expc> actual)
{
    resetable resetable1(*this);
    auto l2 = token_roundo();
    if (l2.has_value())
    {
        for (auto i3 = l2.value(); i3 != 0; i3--)
        {
            next();
        }
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
    if (lr_can_expa())
    {
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
    auto l4 = token_roundc();
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
    auto l7 = token_roundo().value();
    for (;l7 != 0; l7--)
    {
        next();
    }
    skip();
    auto val8 = lr_match_expa();
    actual->value = val8;
    skip();
    auto l10 = token_roundc().value();
    for (;l10 != 0; l10--)
    {
        next();
    }
    skip();
    return true;
}
bool yaoosl::parsing::instance::m_scalar_10(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expc> actual)
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
bool yaoosl::parsing::instance::m_integer_11(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expc> actual)
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
bool yaoosl::parsing::instance::alternatives12(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expc> actual)
{
    resetable resetable1(*this);
    if (m_roundO_expA_roundC_9(true, {}))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_roundO_expA_roundC_9(false, actual);
            return true;
        }
    }
    else if (m_scalar_10(true, {}))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_scalar_10(false, actual);
            return true;
        }
    }
    else if (m_integer_11(true, {}))
    {
        if (is_can)
        {
            return true;
        }
        else
        {
            resetable1.reset();
            m_integer_11(false, actual);
            return true;
        }
    }
    resetable1.reset();
    return false;
}
bool yaoosl::parsing::instance::p_can_expc()
{
    resetable resetable1(*this);
    if (!alternatives12(true, {}))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::expc> yaoosl::parsing::instance::p_match_expc()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::expc>();
    resetable resetable2(*this);
    if (alternatives12(true, {}))
    {
        resetable2.reset();
        alternatives12(false, actual);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expA_13(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main> actual)
{
    resetable resetable1(*this);
    if (lr_can_expa())
    {
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
    auto val2 = lr_match_expa();
    actual->root = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::p_can_main()
{
    resetable resetable1(*this);
    if (!m_expA_13(true, {}))
    {
        resetable1.reset();
        return false;
    }
    return true;
}
std::shared_ptr<yaoosl::parsing::instance::main> yaoosl::parsing::instance::p_match_main()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::main>();
    resetable resetable2(*this);
    if (m_expA_13(true, {}))
    {
        resetable2.reset();
        m_expA_13(false, actual);
    }
    else
    {
        report("Something moved wrong (todo: improve error messages)");
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expB_slash_expC_14(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expb> actual)
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
    if (p_can_expc())
    {
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
    auto val6 = p_match_expc();
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op = '/';
    }
    return true;
}
bool yaoosl::parsing::instance::m_expB_star_expC_15(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expb> actual)
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
    if (p_can_expc())
    {
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
    auto val6 = p_match_expc();
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op = '*';
    }
    return true;
}
bool yaoosl::parsing::instance::m_expC_16(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expb> actual)
{
    resetable resetable1(*this);
    if (p_can_expc())
    {
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
    auto val2 = p_match_expc();
    actual->left = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_expb()
{
    resetable resetable1(*this);
    if (!m_expC_16(true, {}))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expB_slash_expC_14(true, {}))
        {
        }
        else if (m_expB_star_expC_15(true, {}))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::expb> yaoosl::parsing::instance::lr_match_expb()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::expb>();
    if (!m_expC_16(false, actual))
    {
        report("Something moved wrong (todo: improve error messages)");
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expB_slash_expC_14(true, {}))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::expb>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expB_slash_expC_14(false, actual);
        }
        else if (m_expB_star_expC_15(true, {}))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::expb>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expB_star_expC_15(false, actual);
        }
        else
        {
            resetable1.reset();
            break;
        }
    }
    return actual;
}
bool yaoosl::parsing::instance::m_expA_plus_expB_17(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expa> actual)
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
    if (lr_can_expb())
    {
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
    auto val6 = lr_match_expb();
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op = '+';
    }
    return true;
}
bool yaoosl::parsing::instance::m_expA_minus_expB_18(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expa> actual)
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
    if (lr_can_expb())
    {
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
    auto val6 = lr_match_expb();
    actual->right = val6;
    skip();
    if (!is_can)
    {
        actual->op = '-';
    }
    return true;
}
bool yaoosl::parsing::instance::m_expB_19(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expa> actual)
{
    resetable resetable1(*this);
    if (lr_can_expb())
    {
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
    auto val2 = lr_match_expb();
    actual->left = val2;
    skip();
    return true;
}
bool yaoosl::parsing::instance::lr_can_expa()
{
    resetable resetable1(*this);
    if (!m_expB_19(true, {}))
    {
        return false;
    }
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expA_plus_expB_17(true, {}))
        {
        }
        else if (m_expA_minus_expB_18(true, {}))
        {
        }
        else
        {
            return true;
        }
    }
}
std::shared_ptr<yaoosl::parsing::instance::expa> yaoosl::parsing::instance::lr_match_expa()
{
    auto actual = std::make_shared<yaoosl::parsing::instance::expa>();
    if (!m_expB_19(false, actual))
    {
        report("Something moved wrong (todo: improve error messages)");
        return {};
    }
    bool is_first2 = true;
    while (true)
    {
        skip();
        resetable resetable1(*this);
        if (m_expA_plus_expB_17(true, {}))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::expa>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expA_plus_expB_17(false, actual);
        }
        else if (m_expA_minus_expB_18(true, {}))
        {
            resetable1.reset();
            if (!is_first2)
            {
                auto tmp_actual3 = actual;
                actual = std::make_shared<yaoosl::parsing::instance::expa>();
                actual->left = tmp_actual3;
            }
            is_first2 = false;
            m_expA_minus_expB_18(false, actual);
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
void yaoosl::parsing::instance::print_tree(std::shared_ptr<expc> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream)
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
    sstream << "expc:\n";
    switch (node->value.index())
    {
        case 0:
        if (std::get<std::shared_ptr<expa>>(node->value))
        {
        }
        else
        {
            return;
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
        print_tree(std::get<std::shared_ptr<expa>>(node->value), v, contents, sstream);
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
    if (node->root)
    {
    }
    else
    {
        return;
    }
    v.push_back(3);
    v.push_back(0);
    v.push_back(0);
    print_tree(node->root, v, contents, sstream);
    v.pop_back();
    v.pop_back();
    v.pop_back();
}
void yaoosl::parsing::instance::print_tree(std::shared_ptr<expb> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream)
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
    sstream << "expb:\n";
    if (node->op.has_value())
    {
    }
    else
    {
        return;
    }
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<expb>>(node->left))
        {
            v.push_back(1);
        }
        else
        {
            v.push_back(3);
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<expc>>(node->left))
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
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<expb>>(node->left))
        {
        }
        else
        {
            return;
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<expc>>(node->left))
        {
        }
        else
        {
            return;
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
        print_tree(std::get<std::shared_ptr<expb>>(node->left), v, contents, sstream);
        break;
        case 1:
        print_tree(std::get<std::shared_ptr<expc>>(node->left), v, contents, sstream);
        break;
    }
    v.pop_back();
    v.pop_back();
    v.pop_back();
    if (node->right)
    {
    }
    else
    {
        return;
    }
    v.push_back(3);
    v.push_back(0);
    v.push_back(0);
    print_tree(node->right, v, contents, sstream);
    v.pop_back();
    v.pop_back();
    v.pop_back();
}
void yaoosl::parsing::instance::print_tree(std::shared_ptr<expa> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream)
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
    sstream << "expa:\n";
    if (node->op.has_value())
    {
    }
    else
    {
        return;
    }
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<expa>>(node->left))
        {
            v.push_back(1);
        }
        else
        {
            v.push_back(3);
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<expb>>(node->left))
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
    switch (node->left.index())
    {
        case 0:
        if (std::get<std::shared_ptr<expa>>(node->left))
        {
        }
        else
        {
            return;
        }
        break;
        case 1:
        if (std::get<std::shared_ptr<expb>>(node->left))
        {
        }
        else
        {
            return;
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
        print_tree(std::get<std::shared_ptr<expa>>(node->left), v, contents, sstream);
        break;
        case 1:
        print_tree(std::get<std::shared_ptr<expb>>(node->left), v, contents, sstream);
        break;
    }
    v.pop_back();
    v.pop_back();
    v.pop_back();
    if (node->right)
    {
    }
    else
    {
        return;
    }
    v.push_back(3);
    v.push_back(0);
    v.push_back(0);
    print_tree(node->right, v, contents, sstream);
    v.pop_back();
    v.pop_back();
    v.pop_back();
}
std::shared_ptr<yaoosl::parsing::instance::main> yaoosl::parsing::instance::parse()
{
    return p_match_main();
}
