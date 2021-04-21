#include <memory>
#include <string>
#include <string_view>
#include <optional>
#include <variant>
#include <sstream>
#include <vector>

namespace yaoosl::parsing
{
    class instance
    {
    private:
        class resetable;
    public:
        class token;
        class exp_nullar;
        class exp_assignment;
        class statement;
        class function_arg;
        class scope;
        class function;
        class while_loop;
        class if_else;
        class control_structure;
        class main;
        class exp_arithmetic_2;
        class exp_arithmetic_1;
        class exp_compare;
        class exp_equality;
        class exp_and;
        class exp_or;
        class exp_nullar_state;
        class exp_assignment_state;
        class statement_state;
        class function_arg_state;
        class scope_state;
        class function_state;
        class while_loop_state;
        class if_else_state;
        class control_structure_state;
        class main_state;
        class exp_arithmetic_2_state;
        class exp_arithmetic_1_state;
        class exp_compare_state;
        class exp_equality_state;
        class exp_and_state;
        class exp_or_state;
    private:
        class resetable
        {
        public:
            instance& m_ref;
            std::string_view m_contents;
            std::string m_file;
            size_t m_line;
            size_t m_column;
            size_t m_offset;
             resetable(instance& ref);
            void reset();
        };
        friend class resetable;
        void skip();
        bool next();
        char current();
        std::optional<size_t> token_integer();
        std::optional<size_t> token_scalar();
        std::optional<size_t> token_slash();
        std::optional<size_t> token_star();
        std::optional<size_t> token_plus();
        std::optional<size_t> token_minus();
        std::optional<size_t> token_underscore();
        std::optional<size_t> token_ident();
        std::optional<size_t> token__round_bracked_open();
        std::optional<size_t> token__round_bracked_close();
        std::optional<size_t> token__less_then_equal();
        std::optional<size_t> token__less_then();
        std::optional<size_t> token__greater_then_equal();
        std::optional<size_t> token__greater_then();
        std::optional<size_t> token__and();
        std::optional<size_t> token__or();
        std::optional<size_t> token__equal();
        std::optional<size_t> token__curly_bracked_open();
        std::optional<size_t> token__curly_bracked_close();
        std::optional<size_t> token__func();
        std::optional<size_t> token__comma();
        std::optional<size_t> token__while();
        std::optional<size_t> token__if();
        std::optional<size_t> token__else();
        bool m_roundbrackedopen_statement_roundbrackedclose_25(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state);
        bool m_scalar_26(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state);
        bool m_integer_27(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state);
        bool m_ident_28(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state);
        bool alternatives29(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state);
        bool p_can_exp_nullar();
        std::shared_ptr<yaoosl::parsing::instance::exp_nullar> p_match_exp_nullar();
        bool m_integer_equal_statement_30(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_assignment>& actual, yaoosl::parsing::instance::exp_assignment_state& state);
        bool p_can_exp_assignment();
        std::shared_ptr<yaoosl::parsing::instance::exp_assignment> p_match_exp_assignment();
        bool m_expassignment_31(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state);
        bool m_expor_32(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state);
        bool alternatives33(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state);
        bool p_can_statement();
        std::shared_ptr<yaoosl::parsing::instance::statement> p_match_statement();
        bool m_ident_34(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function_arg>& actual, yaoosl::parsing::instance::function_arg_state& state);
        bool p_can_function_arg();
        std::shared_ptr<yaoosl::parsing::instance::function_arg> p_match_function_arg();
        bool m_curlybrackedopen_35(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state);
        bool m_controlstructure_36(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state);
        bool m_statement_37(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state);
        bool alternatives38(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state);
        bool m_curlybrackedclose_39(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state);
        bool while40_41(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state);
        bool m_curlybrackedclose_42(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state);
        bool p_can_scope();
        std::shared_ptr<yaoosl::parsing::instance::scope> p_match_scope();
        bool m_func_ident_roundbrackedopen_43(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state);
        bool m_functionarg_44(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state);
        bool m_comma_functionarg_45(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state);
        bool m_roundbrackedclose_46(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state);
        bool while47_48(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state);
        bool m_functionarg_49(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state);
        bool if50_51(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state);
        bool m_roundbrackedclose_scope_52(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state);
        bool p_can_function();
        std::shared_ptr<yaoosl::parsing::instance::function> p_match_function();
        bool m_while_roundbrackedopen_statement_roundbrackedclose_scope_53(bool is_can, std::shared_ptr<yaoosl::parsing::instance::while_loop>& actual, yaoosl::parsing::instance::while_loop_state& state);
        bool p_can_while_loop();
        std::shared_ptr<yaoosl::parsing::instance::while_loop> p_match_while_loop();
        bool m_if_roundbrackedopen_statement_roundbrackedclose_54(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool m_scope_55(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool m_controlstructure_56(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool m_statement_57(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool alternatives58(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool m_else_59(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool m_scope_60(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool m_controlstructure_61(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool m_statement_62(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool alternatives63(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool m_else_64(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool if65_66(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool p_can_if_else();
        std::shared_ptr<yaoosl::parsing::instance::if_else> p_match_if_else();
        bool m_function_67(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state);
        bool m_whileloop_68(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state);
        bool m_ifelse_69(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state);
        bool m_scope_70(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state);
        bool alternatives71(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state);
        bool p_can_control_structure();
        std::shared_ptr<yaoosl::parsing::instance::control_structure> p_match_control_structure();
        bool m_controlstructure_72(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state);
        bool m_statement_73(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state);
        bool alternatives74(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state);
        bool while75_76(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state);
        bool p_can_main();
        std::shared_ptr<yaoosl::parsing::instance::main> p_match_main();
        bool m_exparithmetic2_slash_expnullar_77(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state);
        bool m_exparithmetic2_star_expnullar_78(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state);
        bool m_expnullar_79(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state);
        bool lr_can_exp_arithmetic_2();
        std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> lr_match_exp_arithmetic_2();
        bool m_exparithmetic1_plus_exparithmetic2_80(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state);
        bool m_exparithmetic1_minus_exparithmetic2_81(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state);
        bool m_exparithmetic2_82(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state);
        bool lr_can_exp_arithmetic_1();
        std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> lr_match_exp_arithmetic_1();
        bool m_expcompare_lessthenequal_exparithmetic1_83(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state);
        bool m_expcompare_lessthen_exparithmetic1_84(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state);
        bool m_expcompare_greaterthenequal_exparithmetic1_85(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state);
        bool m_expcompare_greaterthen_exparithmetic1_86(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state);
        bool m_exparithmetic1_87(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state);
        bool lr_can_exp_compare();
        std::shared_ptr<yaoosl::parsing::instance::exp_compare> lr_match_exp_compare();
        bool m_expequality_lessthenequal_expcompare_88(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state);
        bool m_expequality_lessthen_expcompare_89(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state);
        bool m_expequality_greaterthenequal_expcompare_90(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state);
        bool m_expequality_greaterthen_expcompare_91(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state);
        bool m_expcompare_92(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state);
        bool lr_can_exp_equality();
        std::shared_ptr<yaoosl::parsing::instance::exp_equality> lr_match_exp_equality();
        bool m_expand_and_expequality_93(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and>& actual, yaoosl::parsing::instance::exp_and_state& state);
        bool m_expequality_94(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and>& actual, yaoosl::parsing::instance::exp_and_state& state);
        bool lr_can_exp_and();
        std::shared_ptr<yaoosl::parsing::instance::exp_and> lr_match_exp_and();
        bool m_expor_or_expequality_95(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or>& actual, yaoosl::parsing::instance::exp_or_state& state);
        bool m_expequality_96(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or>& actual, yaoosl::parsing::instance::exp_or_state& state);
        bool lr_can_exp_or();
        std::shared_ptr<yaoosl::parsing::instance::exp_or> lr_match_exp_or();
    protected:
        std::string_view m_contents;
        std::string m_file;
        size_t m_line;
        size_t m_column;
        size_t m_offset;
        virtual void report(std::string_view message);
    public:
        instance(std::string_view contents, std::string file) : m_contents(contents), m_file(file), m_line(1), m_column(1), m_offset(0)
        {
        }
        enum class tok
        {
            INTEGER,
            SCALAR,
            SLASH,
            STAR,
            PLUS,
            MINUS,
            UNDERSCORE,
            IDENT,
            _ROUND_BRACKED_OPEN,
            _ROUND_BRACKED_CLOSE,
            _LESS_THEN_EQUAL,
            _LESS_THEN,
            _GREATER_THEN_EQUAL,
            _GREATER_THEN,
            _AND,
            _OR,
            _EQUAL,
            _CURLY_BRACKED_OPEN,
            _CURLY_BRACKED_CLOSE,
            _FUNC,
            _COMMA,
            _WHILE,
            _IF,
            _ELSE,
            __MAX__
        };
        class token
        {
        public:
            tok type;
            std::string file;
            size_t line;
            size_t column;
            size_t offset;
            size_t length;
        };
        yaoosl::parsing::instance::token create_token(size_t length, tok type);
        class exp_nullar
        {
        public:
            std::variant<std::shared_ptr<statement>, token> value;
        };
        class exp_assignment
        {
        public:
            token name;
            std::shared_ptr<statement> value;
        };
        class statement
        {
        public:
            std::variant<std::shared_ptr<exp_assignment>, std::shared_ptr<exp_or>> expression;
        };
        class function_arg
        {
        public:
            token name;
        };
        class scope
        {
        public:
            std::vector<std::variant<std::shared_ptr<control_structure>, std::shared_ptr<statement>>> body;
        };
        class function
        {
        public:
            token name;
            std::vector<std::shared_ptr<function_arg>> args;
            std::shared_ptr<scope> body;
        };
        class while_loop
        {
        public:
            std::shared_ptr<statement> condition;
            std::shared_ptr<scope> body;
        };
        class if_else
        {
        public:
            std::shared_ptr<statement> condition;
            std::variant<std::shared_ptr<scope>, std::shared_ptr<control_structure>, std::shared_ptr<statement>> if_body;
            std::variant<std::shared_ptr<scope>, std::shared_ptr<control_structure>, std::shared_ptr<statement>> else_body;
        };
        class control_structure
        {
        public:
            std::variant<std::shared_ptr<function>, std::shared_ptr<while_loop>, std::shared_ptr<if_else>, std::shared_ptr<scope>> content;
        };
        class main
        {
        public:
            std::vector<std::variant<std::shared_ptr<control_structure>, std::shared_ptr<statement>>> content;
        };
        class exp_arithmetic_2
        {
        public:
            std::optional<char> op;
            std::variant<std::shared_ptr<exp_arithmetic_2>, std::shared_ptr<exp_nullar>> left;
            std::shared_ptr<exp_nullar> right;
        };
        class exp_arithmetic_1
        {
        public:
            std::optional<char> op;
            std::variant<std::shared_ptr<exp_arithmetic_1>, std::shared_ptr<exp_arithmetic_2>> left;
            std::shared_ptr<exp_arithmetic_2> right;
        };
        class exp_compare
        {
        public:
            std::optional<char> op1;
            std::optional<char> eq2;
            std::optional<char> op2;
            std::variant<std::shared_ptr<exp_compare>, std::shared_ptr<exp_arithmetic_1>> left;
            std::shared_ptr<exp_arithmetic_1> right;
        };
        class exp_equality
        {
        public:
            std::optional<char> op1;
            std::optional<char> eq2;
            std::optional<char> op2;
            std::variant<std::shared_ptr<exp_equality>, std::shared_ptr<exp_compare>> left;
            std::shared_ptr<exp_compare> right;
        };
        class exp_and
        {
        public:
            std::variant<std::shared_ptr<exp_and>, std::shared_ptr<exp_equality>> left;
            std::shared_ptr<exp_equality> right;
        };
        class exp_or
        {
        public:
            std::variant<std::shared_ptr<exp_or>, std::shared_ptr<exp_equality>> left;
            std::shared_ptr<exp_equality> right;
        };
        class exp_nullar_state
        {
        };
        class exp_assignment_state
        {
        };
        class statement_state
        {
        };
        class function_arg_state
        {
        };
        class scope_state
        {
        };
        class function_state
        {
        };
        class while_loop_state
        {
        };
        class if_else_state
        {
        };
        class control_structure_state
        {
        };
        class main_state
        {
        };
        class exp_arithmetic_2_state
        {
        };
        class exp_arithmetic_1_state
        {
        };
        class exp_compare_state
        {
        };
        class exp_equality_state
        {
        };
        class exp_and_state
        {
        };
        class exp_or_state
        {
        };
        std::shared_ptr<yaoosl::parsing::instance::main> parse();
        void print_tree(std::shared_ptr<exp_nullar> node, std::vector<char> v, std::string_view contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<exp_assignment> node, std::vector<char> v, std::string_view contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<statement> node, std::vector<char> v, std::string_view contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<function_arg> node, std::vector<char> v, std::string_view contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<scope> node, std::vector<char> v, std::string_view contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<function> node, std::vector<char> v, std::string_view contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<while_loop> node, std::vector<char> v, std::string_view contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<if_else> node, std::vector<char> v, std::string_view contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<control_structure> node, std::vector<char> v, std::string_view contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<main> node, std::vector<char> v, std::string_view contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<exp_arithmetic_2> node, std::vector<char> v, std::string_view contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<exp_arithmetic_1> node, std::vector<char> v, std::string_view contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<exp_compare> node, std::vector<char> v, std::string_view contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<exp_equality> node, std::vector<char> v, std::string_view contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<exp_and> node, std::vector<char> v, std::string_view contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<exp_or> node, std::vector<char> v, std::string_view contents, std::stringstream& sstream);
    };
}
