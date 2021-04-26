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
        class call;
        class exp_nullar;
        class exp_assignment;
        class return_statement;
        class expression;
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
        class call_state;
        class exp_nullar_state;
        class exp_assignment_state;
        class return_statement_state;
        class expression_state;
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
        std::optional<size_t> token__comma();
        std::optional<size_t> token__less_then_equal();
        std::optional<size_t> token__less_then();
        std::optional<size_t> token__greater_then_equal();
        std::optional<size_t> token__greater_then();
        std::optional<size_t> token__and();
        std::optional<size_t> token__or();
        std::optional<size_t> token__equal();
        std::optional<size_t> token__return();
        std::optional<size_t> token__auto_77();
        std::optional<size_t> token__curly_bracked_open();
        std::optional<size_t> token__curly_bracked_close();
        std::optional<size_t> token__func();
        std::optional<size_t> token__while();
        std::optional<size_t> token__if();
        std::optional<size_t> token__else();
        bool m_ident_roundbrackedopen_27(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state);
        bool m_expression_28(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state);
        bool m_comma_expression_29(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state);
        bool m_roundbrackedclose_30(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state);
        bool while31_32(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state);
        bool m_expression_33(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state);
        bool if34_35(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state);
        bool m_roundbrackedclose_36(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state);
        bool p_can_call();
        std::shared_ptr<yaoosl::parsing::instance::call> p_match_call();
        bool m_roundbrackedopen_statement_roundbrackedclose_37(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state);
        bool m_scalar_38(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state);
        bool m_integer_39(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state);
        bool m_call_40(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state);
        bool m_ident_41(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state);
        bool alternatives42(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state);
        bool p_can_exp_nullar();
        std::shared_ptr<yaoosl::parsing::instance::exp_nullar> p_match_exp_nullar();
        bool m_equal_statement_43(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_assignment>& actual, yaoosl::parsing::instance::exp_assignment_state& state);
        bool p_can_exp_assignment();
        std::shared_ptr<yaoosl::parsing::instance::exp_assignment> p_match_exp_assignment();
        bool m_return_expor_44(bool is_can, std::shared_ptr<yaoosl::parsing::instance::return_statement>& actual, yaoosl::parsing::instance::return_statement_state& state);
        bool p_can_return_statement();
        std::shared_ptr<yaoosl::parsing::instance::return_statement> p_match_return_statement();
        bool m_expassignment_45(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expression>& actual, yaoosl::parsing::instance::expression_state& state);
        bool m_expor_46(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expression>& actual, yaoosl::parsing::instance::expression_state& state);
        bool alternatives47(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expression>& actual, yaoosl::parsing::instance::expression_state& state);
        bool p_can_expression();
        std::shared_ptr<yaoosl::parsing::instance::expression> p_match_expression();
        bool m_returnstatement_auto77_48(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state);
        bool m_expression_auto77_49(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state);
        bool m_auto77_50(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state);
        bool alternatives51(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state);
        bool p_can_statement();
        std::shared_ptr<yaoosl::parsing::instance::statement> p_match_statement();
        bool m_ident_52(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function_arg>& actual, yaoosl::parsing::instance::function_arg_state& state);
        bool p_can_function_arg();
        std::shared_ptr<yaoosl::parsing::instance::function_arg> p_match_function_arg();
        bool m_curlybrackedopen_53(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state);
        bool m_controlstructure_54(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state);
        bool m_statement_55(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state);
        bool alternatives56(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state);
        bool m_curlybrackedclose_57(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state);
        bool while58_59(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state);
        bool m_curlybrackedclose_60(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state);
        bool p_can_scope();
        std::shared_ptr<yaoosl::parsing::instance::scope> p_match_scope();
        bool m_func_ident_roundbrackedopen_61(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state);
        bool m_functionarg_62(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state);
        bool m_comma_functionarg_63(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state);
        bool m_roundbrackedclose_64(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state);
        bool while65_66(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state);
        bool m_functionarg_67(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state);
        bool if68_69(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state);
        bool m_roundbrackedclose_scope_70(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state);
        bool p_can_function();
        std::shared_ptr<yaoosl::parsing::instance::function> p_match_function();
        bool m_while_roundbrackedopen_statement_roundbrackedclose_scope_71(bool is_can, std::shared_ptr<yaoosl::parsing::instance::while_loop>& actual, yaoosl::parsing::instance::while_loop_state& state);
        bool p_can_while_loop();
        std::shared_ptr<yaoosl::parsing::instance::while_loop> p_match_while_loop();
        bool m_if_roundbrackedopen_statement_roundbrackedclose_72(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool m_scope_73(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool m_controlstructure_74(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool m_statement_75(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool alternatives76(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool m_else_77(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool m_scope_78(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool m_controlstructure_79(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool m_statement_80(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool alternatives81(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool m_else_82(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool if83_84(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state);
        bool p_can_if_else();
        std::shared_ptr<yaoosl::parsing::instance::if_else> p_match_if_else();
        bool m_function_85(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state);
        bool m_whileloop_86(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state);
        bool m_ifelse_87(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state);
        bool m_scope_88(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state);
        bool alternatives89(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state);
        bool p_can_control_structure();
        std::shared_ptr<yaoosl::parsing::instance::control_structure> p_match_control_structure();
        bool m_controlstructure_90(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state);
        bool m_statement_91(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state);
        bool alternatives92(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state);
        bool while93_94(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state);
        bool p_can_main();
        std::shared_ptr<yaoosl::parsing::instance::main> p_match_main();
        bool m_exparithmetic2_slash_expnullar_95(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state);
        bool m_exparithmetic2_star_expnullar_96(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state);
        bool m_expnullar_97(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state);
        bool lr_can_exp_arithmetic_2();
        std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> lr_match_exp_arithmetic_2();
        bool m_exparithmetic1_plus_exparithmetic2_98(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state);
        bool m_exparithmetic1_minus_exparithmetic2_99(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state);
        bool m_exparithmetic2_100(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state);
        bool lr_can_exp_arithmetic_1();
        std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> lr_match_exp_arithmetic_1();
        bool m_expcompare_lessthenequal_exparithmetic1_101(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state);
        bool m_expcompare_lessthen_exparithmetic1_102(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state);
        bool m_expcompare_greaterthenequal_exparithmetic1_103(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state);
        bool m_expcompare_greaterthen_exparithmetic1_104(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state);
        bool m_exparithmetic1_105(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state);
        bool lr_can_exp_compare();
        std::shared_ptr<yaoosl::parsing::instance::exp_compare> lr_match_exp_compare();
        bool m_expequality_lessthenequal_expcompare_106(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state);
        bool m_expequality_lessthen_expcompare_107(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state);
        bool m_expequality_greaterthenequal_expcompare_108(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state);
        bool m_expequality_greaterthen_expcompare_109(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state);
        bool m_expcompare_110(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state);
        bool lr_can_exp_equality();
        std::shared_ptr<yaoosl::parsing::instance::exp_equality> lr_match_exp_equality();
        bool m_expand_and_expequality_111(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and>& actual, yaoosl::parsing::instance::exp_and_state& state);
        bool m_expequality_112(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and>& actual, yaoosl::parsing::instance::exp_and_state& state);
        bool lr_can_exp_and();
        std::shared_ptr<yaoosl::parsing::instance::exp_and> lr_match_exp_and();
        bool m_expor_or_expequality_113(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or>& actual, yaoosl::parsing::instance::exp_or_state& state);
        bool m_expequality_114(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or>& actual, yaoosl::parsing::instance::exp_or_state& state);
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
            _COMMA,
            _LESS_THEN_EQUAL,
            _LESS_THEN,
            _GREATER_THEN_EQUAL,
            _GREATER_THEN,
            _AND,
            _OR,
            _EQUAL,
            _RETURN,
            _AUTO_77,
            _CURLY_BRACKED_OPEN,
            _CURLY_BRACKED_CLOSE,
            _FUNC,
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
        class call
        {
        public:
            token method;
            std::vector<std::shared_ptr<expression>> args;
        };
        class exp_nullar
        {
        public:
            std::variant<std::shared_ptr<statement>, token, std::shared_ptr<call>> value;
        };
        class exp_assignment
        {
        public:
            token name;
            std::shared_ptr<statement> value;
        };
        class return_statement
        {
        public:
            std::shared_ptr<exp_or> expression;
        };
        class expression
        {
        public:
            std::variant<std::shared_ptr<exp_assignment>, std::shared_ptr<exp_or>> expression;
        };
        class statement
        {
        public:
            std::variant<std::shared_ptr<return_statement>, std::shared_ptr<expression>> expression;
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
        class call_state
        {
        };
        class exp_nullar_state
        {
        };
        class exp_assignment_state
        {
        };
        class return_statement_state
        {
        };
        class expression_state
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
        std::vector<std::string> create_string_tree(std::shared_ptr<call> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_nullar> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_assignment> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<return_statement> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<expression> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<statement> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<function_arg> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<scope> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<function> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<while_loop> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<if_else> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<control_structure> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<main> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_arithmetic_2> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_arithmetic_1> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_compare> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_equality> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_and> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_or> node, std::string_view contents);
    };
}
