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
        std::optional<size_t> token__auto_7();
        std::optional<size_t> token__auto_9();
        std::optional<size_t> token__auto_28();
        std::optional<size_t> token__auto_31();
        std::optional<size_t> token__auto_34();
        std::optional<size_t> token__auto_37();
        std::optional<size_t> token__auto_54();
        std::optional<size_t> token__auto_58();
        std::optional<size_t> token__auto_62();
        std::optional<size_t> token__auto_67();
        std::optional<size_t> token__auto_68();
        std::optional<size_t> token__auto_72();
        std::optional<size_t> token__auto_78();
        std::optional<size_t> token__auto_82();
        std::optional<size_t> token__auto_87();
        std::optional<size_t> token__auto_94();
        bool m_auto7_statement_auto9_25(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar> actual);
        bool m_scalar_26(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar> actual);
        bool m_integer_27(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar> actual);
        bool m_ident_28(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar> actual);
        bool alternatives29(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar> actual);
        bool p_can_exp_nullar();
        std::shared_ptr<yaoosl::parsing::instance::exp_nullar> p_match_exp_nullar();
        bool m_integer_auto62_statement_30(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_assignment> actual);
        bool p_can_exp_assignment();
        std::shared_ptr<yaoosl::parsing::instance::exp_assignment> p_match_exp_assignment();
        bool m_expassignment_31(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement> actual);
        bool m_expor_32(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement> actual);
        bool alternatives33(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement> actual);
        bool p_can_statement();
        std::shared_ptr<yaoosl::parsing::instance::statement> p_match_statement();
        bool m_ident_34(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function_arg> actual);
        bool p_can_function_arg();
        std::shared_ptr<yaoosl::parsing::instance::function_arg> p_match_function_arg();
        bool m_auto67_35(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope> actual);
        bool m_controlstructure_36(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope> actual);
        bool m_statement_37(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope> actual);
        bool alternatives38(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope> actual);
        bool m_auto68_39(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope> actual);
        bool while40_41(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope> actual);
        bool m_auto68_42(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope> actual);
        bool p_can_scope();
        std::shared_ptr<yaoosl::parsing::instance::scope> p_match_scope();
        bool m_auto72_ident_auto7_43(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function> actual);
        bool m_functionarg_44(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function> actual);
        bool m_auto78_functionarg_45(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function> actual);
        bool m_auto9_46(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function> actual);
        bool while47_48(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function> actual);
        bool m_functionarg_49(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function> actual);
        bool if50_51(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function> actual);
        bool m_auto9_scope_52(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function> actual);
        bool p_can_function();
        std::shared_ptr<yaoosl::parsing::instance::function> p_match_function();
        bool m_auto82_auto7_statement_auto9_scope_53(bool is_can, std::shared_ptr<yaoosl::parsing::instance::while_loop> actual);
        bool p_can_while_loop();
        std::shared_ptr<yaoosl::parsing::instance::while_loop> p_match_while_loop();
        bool m_auto87_auto7_statement_auto9_54(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual);
        bool m_scope_55(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual);
        bool m_controlstructure_56(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual);
        bool m_statement_57(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual);
        bool alternatives58(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual);
        bool m_auto94_59(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual);
        bool m_scope_60(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual);
        bool m_controlstructure_61(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual);
        bool m_statement_62(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual);
        bool alternatives63(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual);
        bool m_auto94_64(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual);
        bool if65_66(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else> actual);
        bool p_can_if_else();
        std::shared_ptr<yaoosl::parsing::instance::if_else> p_match_if_else();
        bool m_function_67(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure> actual);
        bool m_whileloop_68(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure> actual);
        bool m_ifelse_69(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure> actual);
        bool m_scope_70(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure> actual);
        bool alternatives71(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure> actual);
        bool p_can_control_structure();
        std::shared_ptr<yaoosl::parsing::instance::control_structure> p_match_control_structure();
        bool m_controlstructure_72(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main> actual);
        bool m_statement_73(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main> actual);
        bool alternatives74(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main> actual);
        bool p_can_main();
        std::shared_ptr<yaoosl::parsing::instance::main> p_match_main();
        bool m_exparithmetic2_slash_expnullar_75(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> actual);
        bool m_exparithmetic2_star_expnullar_76(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> actual);
        bool m_expnullar_77(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> actual);
        bool lr_can_exp_arithmetic_2();
        std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> lr_match_exp_arithmetic_2();
        bool m_exparithmetic1_plus_exparithmetic2_78(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> actual);
        bool m_exparithmetic1_minus_exparithmetic2_79(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> actual);
        bool m_exparithmetic2_80(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> actual);
        bool lr_can_exp_arithmetic_1();
        std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> lr_match_exp_arithmetic_1();
        bool m_expcompare_auto28_exparithmetic1_81(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare> actual);
        bool m_expcompare_auto31_exparithmetic1_82(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare> actual);
        bool m_expcompare_auto34_exparithmetic1_83(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare> actual);
        bool m_expcompare_auto37_exparithmetic1_84(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare> actual);
        bool m_exparithmetic1_85(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare> actual);
        bool lr_can_exp_compare();
        std::shared_ptr<yaoosl::parsing::instance::exp_compare> lr_match_exp_compare();
        bool m_expequality_auto28_expcompare_86(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality> actual);
        bool m_expequality_auto31_expcompare_87(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality> actual);
        bool m_expequality_auto34_expcompare_88(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality> actual);
        bool m_expequality_auto37_expcompare_89(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality> actual);
        bool m_expcompare_90(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality> actual);
        bool lr_can_exp_equality();
        std::shared_ptr<yaoosl::parsing::instance::exp_equality> lr_match_exp_equality();
        bool m_expand_auto54_expequality_91(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and> actual);
        bool m_expequality_92(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and> actual);
        bool lr_can_exp_and();
        std::shared_ptr<yaoosl::parsing::instance::exp_and> lr_match_exp_and();
        bool m_expor_auto58_expequality_93(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or> actual);
        bool m_expequality_94(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or> actual);
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
            _AUTO_7,
            _AUTO_9,
            _AUTO_28,
            _AUTO_31,
            _AUTO_34,
            _AUTO_37,
            _AUTO_54,
            _AUTO_58,
            _AUTO_62,
            _AUTO_67,
            _AUTO_68,
            _AUTO_72,
            _AUTO_78,
            _AUTO_82,
            _AUTO_87,
            _AUTO_94,
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
        };
        class function_arg
        {
        public:
            token name;
        };
        class scope
        {
        };
        class function
        {
        public:
            token name;
            std::shared_ptr<function_arg> args;
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
        };
        class main
        {
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
        void print_tree(std::shared_ptr<exp_nullar> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<exp_assignment> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<statement> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<function_arg> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<scope> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<function> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<while_loop> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<if_else> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<control_structure> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<main> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<exp_arithmetic_2> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<exp_arithmetic_1> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<exp_compare> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<exp_equality> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<exp_and> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<exp_or> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        std::shared_ptr<yaoosl::parsing::instance::main> parse();
    };
}
