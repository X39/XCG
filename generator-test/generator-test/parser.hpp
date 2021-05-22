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
        class template_usage_item;
        class template_usage;
        class template_definition_item;
        class template_definition;
        class exp_chain_start;
        class exp_chain_indexer;
        class exp_chain_access;
        class exp_chain_call;
        class type_match;
        class typeof;
        class nameof;
        class string_literal;
        class exp_value;
        class exp_nullar;
        class exp_unary;
        class return_statement;
        class declaration;
        class statement;
        class function_arg;
        class scope;
        class scope_getset;
        class function;
        class control_structure_body;
        class while_loop;
        class if_else;
        class switch_case;
        class switch_;
        class control_structure;
        class encapsulation;
        class namespace_;
        class class_;
        class method_arglist_item_with_default;
        class method_arglist_item;
        class method_arglist;
        class method_arglist_indexer;
        class method_ident;
        class method;
        class constructor;
        class destructor;
        class copystructor;
        class conversion;
        class indexer;
        class operator_binary_overload;
        class operator_unary_overload;
        class property;
        class main;
        class exp_chain;
        class ident_navigation;
        class type_navigation;
        class exp_binary_3;
        class exp_binary_2;
        class exp_binary_1;
        class exp_arithmetic_2;
        class exp_arithmetic_1;
        class exp_compare;
        class exp_equality;
        class exp_and;
        class exp_or;
        class expression;
        class call_state;
        class template_usage_item_state;
        class template_usage_state;
        class template_definition_item_state;
        class template_definition_state;
        class exp_chain_start_state;
        class exp_chain_indexer_state;
        class exp_chain_access_state;
        class exp_chain_call_state;
        class type_match_state;
        class typeof_state;
        class nameof_state;
        class string_literal_state;
        class exp_value_state;
        class exp_nullar_state;
        class exp_unary_state;
        class return_statement_state;
        class declaration_state;
        class statement_state;
        class function_arg_state;
        class scope_state;
        class scope_getset_state;
        class function_state;
        class control_structure_body_state;
        class while_loop_state;
        class if_else_state;
        class switch_case_state;
        class switch__state;
        class control_structure_state;
        class encapsulation_state;
        class namespace__state;
        class class__state;
        class method_arglist_item_with_default_state;
        class method_arglist_item_state;
        class method_arglist_state;
        class method_arglist_indexer_state;
        class method_ident_state;
        class method_state;
        class constructor_state;
        class destructor_state;
        class copystructor_state;
        class conversion_state;
        class indexer_state;
        class operator_binary_overload_state;
        class operator_unary_overload_state;
        class property_state;
        class main_state;
        class exp_chain_state;
        class ident_navigation_state;
        class type_navigation_state;
        class exp_binary_3_state;
        class exp_binary_2_state;
        class exp_binary_1_state;
        class exp_arithmetic_2_state;
        class exp_arithmetic_1_state;
        class exp_compare_state;
        class exp_equality_state;
        class exp_and_state;
        class exp_or_state;
        class expression_state;
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
        bool next();
        char current();
        std::optional<size_t> token_integer(size_t depth);
        std::optional<size_t> token_scalar(size_t depth);
        std::optional<size_t> token_slash(size_t depth);
        std::optional<size_t> token_star(size_t depth);
        std::optional<size_t> token_plus(size_t depth);
        std::optional<size_t> token_minus(size_t depth);
        std::optional<size_t> token_underscore(size_t depth);
        std::optional<size_t> token_true_(size_t depth);
        std::optional<size_t> token_false_(size_t depth);
        std::optional<size_t> token_boolean(size_t depth);
        std::optional<size_t> token_ident(size_t depth);
        std::optional<size_t> token_string(size_t depth);
        std::optional<size_t> token__round_bracked_open(size_t depth);
        std::optional<size_t> token__round_bracked_close(size_t depth);
        std::optional<size_t> token__comma(size_t depth);
        std::optional<size_t> token__less_then(size_t depth);
        std::optional<size_t> token__greater_then(size_t depth);
        std::optional<size_t> token__equal(size_t depth);
        std::optional<size_t> token__square_bracked_open(size_t depth);
        std::optional<size_t> token__square_bracked_close(size_t depth);
        std::optional<size_t> token__dot(size_t depth);
        std::optional<size_t> token__typeof(size_t depth);
        std::optional<size_t> token__nameof(size_t depth);
        std::optional<size_t> token__exclamation(size_t depth);
        std::optional<size_t> token__tilde(size_t depth);
        std::optional<size_t> token__less_then_less_then(size_t depth);
        std::optional<size_t> token__greater_then_greater_then(size_t depth);
        std::optional<size_t> token__less_then_less_then_less_then(size_t depth);
        std::optional<size_t> token__greater_then_greater_then_greater_then(size_t depth);
        std::optional<size_t> token__ampersand(size_t depth);
        std::optional<size_t> token__vertical_bar(size_t depth);
        std::optional<size_t> token__less_then_equal(size_t depth);
        std::optional<size_t> token__greater_then_equal(size_t depth);
        std::optional<size_t> token__ampersand_ampersand(size_t depth);
        std::optional<size_t> token__vertical_bar_vertical_bar(size_t depth);
        std::optional<size_t> token__return(size_t depth);
        std::optional<size_t> token__semicolon(size_t depth);
        std::optional<size_t> token__curly_bracked_open(size_t depth);
        std::optional<size_t> token__curly_bracked_close(size_t depth);
        std::optional<size_t> token__get(size_t depth);
        std::optional<size_t> token__set(size_t depth);
        std::optional<size_t> token__func(size_t depth);
        std::optional<size_t> token__while(size_t depth);
        std::optional<size_t> token__if(size_t depth);
        std::optional<size_t> token__else(size_t depth);
        std::optional<size_t> token__case(size_t depth);
        std::optional<size_t> token__colon(size_t depth);
        std::optional<size_t> token__switch(size_t depth);
        std::optional<size_t> token__default(size_t depth);
        std::optional<size_t> token__public(size_t depth);
        std::optional<size_t> token__local(size_t depth);
        std::optional<size_t> token__derived(size_t depth);
        std::optional<size_t> token__private(size_t depth);
        std::optional<size_t> token__namespace(size_t depth);
        std::optional<size_t> token__class(size_t depth);
        std::optional<size_t> token__unbound(size_t depth);
        std::optional<size_t> token__delete(size_t depth);
        std::optional<size_t> token__conversion(size_t depth);
        std::optional<size_t> token__operator(size_t depth);
        bool m_ident_roundbrackedopen_60(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool m_expression_61(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool m_expression_62(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool m_roundbrackedclose_63(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool m_comma_expression_64(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool m_comma_65(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool alternatives66(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool while67_68(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool if69_70(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool m_roundbrackedclose_71(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool p_can_call(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::call> p_match_call(size_t depth);
        bool m_ident_72(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage_item>& actual, yaoosl::parsing::instance::template_usage_item_state& state, size_t depth);
        bool p_can_template_usage_item(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::template_usage_item> p_match_template_usage_item(size_t depth);
        bool m_lessthen_73(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth);
        bool m_templateusageitem_74(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth);
        bool m_comma_75(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth);
        bool m_comma_templateusageitem_76(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth);
        bool alternatives77(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth);
        bool while78_79(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth);
        bool m_greaterthen_80(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth);
        bool p_can_template_usage(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::template_usage> p_match_template_usage(size_t depth);
        bool m_ident_81(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition_item>& actual, yaoosl::parsing::instance::template_definition_item_state& state, size_t depth);
        bool m_equal_82(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition_item>& actual, yaoosl::parsing::instance::template_definition_item_state& state, size_t depth);
        bool m_equal_expvalue_83(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition_item>& actual, yaoosl::parsing::instance::template_definition_item_state& state, size_t depth);
        bool if84_85(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition_item>& actual, yaoosl::parsing::instance::template_definition_item_state& state, size_t depth);
        bool p_can_template_definition_item(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::template_definition_item> p_match_template_definition_item(size_t depth);
        bool m_lessthen_86(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth);
        bool m_templatedefinitionitem_87(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth);
        bool m_comma_88(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth);
        bool m_comma_templatedefinitionitem_89(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth);
        bool alternatives90(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth);
        bool while91_92(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth);
        bool m_greaterthen_93(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth);
        bool p_can_template_definition(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::template_definition> p_match_template_definition(size_t depth);
        bool m_call_94(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_start>& actual, yaoosl::parsing::instance::exp_chain_start_state& state, size_t depth);
        bool m_ident_95(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_start>& actual, yaoosl::parsing::instance::exp_chain_start_state& state, size_t depth);
        bool alternatives96(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_start>& actual, yaoosl::parsing::instance::exp_chain_start_state& state, size_t depth);
        bool p_can_exp_chain_start(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_chain_start> p_match_exp_chain_start(size_t depth);
        bool m_squarebrackedopen_97(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_indexer>& actual, yaoosl::parsing::instance::exp_chain_indexer_state& state, size_t depth);
        bool m_squarebrackedclose_98(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_indexer>& actual, yaoosl::parsing::instance::exp_chain_indexer_state& state, size_t depth);
        bool p_can_exp_chain_indexer(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_chain_indexer> p_match_exp_chain_indexer(size_t depth);
        bool m_dot_ident_99(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_access>& actual, yaoosl::parsing::instance::exp_chain_access_state& state, size_t depth);
        bool p_can_exp_chain_access(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_chain_access> p_match_exp_chain_access(size_t depth);
        bool m_dot_call_100(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_call>& actual, yaoosl::parsing::instance::exp_chain_call_state& state, size_t depth);
        bool p_can_exp_chain_call(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_chain_call> p_match_exp_chain_call(size_t depth);
        bool m_typenavigation_squarebrackedopen_expvalue_squarebrackedclose_101(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_match>& actual, yaoosl::parsing::instance::type_match_state& state, size_t depth);
        bool m_typenavigation_squarebrackedopen_squarebrackedclose_102(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_match>& actual, yaoosl::parsing::instance::type_match_state& state, size_t depth);
        bool m_typenavigation_103(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_match>& actual, yaoosl::parsing::instance::type_match_state& state, size_t depth);
        bool alternatives104(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_match>& actual, yaoosl::parsing::instance::type_match_state& state, size_t depth);
        bool p_can_type_match(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::type_match> p_match_type_match(size_t depth);
        bool m_typeof_roundbrackedopen_typematch_roundbrackedclose_105(bool is_can, std::shared_ptr<yaoosl::parsing::instance::typeof>& actual, yaoosl::parsing::instance::typeof_state& state, size_t depth);
        bool p_can_typeof(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::typeof> p_match_typeof(size_t depth);
        bool m_nameof_roundbrackedopen_expor_roundbrackedclose_106(bool is_can, std::shared_ptr<yaoosl::parsing::instance::nameof>& actual, yaoosl::parsing::instance::nameof_state& state, size_t depth);
        bool p_can_nameof(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::nameof> p_match_nameof(size_t depth);
        bool m_ident_string_ident_107(bool is_can, std::shared_ptr<yaoosl::parsing::instance::string_literal>& actual, yaoosl::parsing::instance::string_literal_state& state, size_t depth);
        bool m_string_ident_108(bool is_can, std::shared_ptr<yaoosl::parsing::instance::string_literal>& actual, yaoosl::parsing::instance::string_literal_state& state, size_t depth);
        bool m_ident_string_109(bool is_can, std::shared_ptr<yaoosl::parsing::instance::string_literal>& actual, yaoosl::parsing::instance::string_literal_state& state, size_t depth);
        bool m_string_110(bool is_can, std::shared_ptr<yaoosl::parsing::instance::string_literal>& actual, yaoosl::parsing::instance::string_literal_state& state, size_t depth);
        bool alternatives111(bool is_can, std::shared_ptr<yaoosl::parsing::instance::string_literal>& actual, yaoosl::parsing::instance::string_literal_state& state, size_t depth);
        bool p_can_string_literal(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::string_literal> p_match_string_literal(size_t depth);
        bool m_typeof_112(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth);
        bool m_nameof_113(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth);
        bool m_scalar_114(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth);
        bool m_boolean_115(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth);
        bool m_stringliteral_116(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth);
        bool m_integer_117(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth);
        bool alternatives118(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth);
        bool p_can_exp_value(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_value> p_match_exp_value(size_t depth);
        bool m_roundbrackedopen_statement_roundbrackedclose_119(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth);
        bool m_declaration_120(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth);
        bool m_expchain_121(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth);
        bool m_expvalue_122(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth);
        bool alternatives123(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth);
        bool p_can_exp_nullar(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_nullar> p_match_exp_nullar(size_t depth);
        bool m_exclamation_expunary_124(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_unary>& actual, yaoosl::parsing::instance::exp_unary_state& state, size_t depth);
        bool m_tilde_expunary_125(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_unary>& actual, yaoosl::parsing::instance::exp_unary_state& state, size_t depth);
        bool m_minus_expunary_126(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_unary>& actual, yaoosl::parsing::instance::exp_unary_state& state, size_t depth);
        bool m_plus_expunary_127(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_unary>& actual, yaoosl::parsing::instance::exp_unary_state& state, size_t depth);
        bool m_expnullar_128(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_unary>& actual, yaoosl::parsing::instance::exp_unary_state& state, size_t depth);
        bool alternatives129(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_unary>& actual, yaoosl::parsing::instance::exp_unary_state& state, size_t depth);
        bool p_can_exp_unary(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_unary> p_match_exp_unary(size_t depth);
        bool m_return_expor_130(bool is_can, std::shared_ptr<yaoosl::parsing::instance::return_statement>& actual, yaoosl::parsing::instance::return_statement_state& state, size_t depth);
        bool p_can_return_statement(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::return_statement> p_match_return_statement(size_t depth);
        bool m_typematch_ident_131(bool is_can, std::shared_ptr<yaoosl::parsing::instance::declaration>& actual, yaoosl::parsing::instance::declaration_state& state, size_t depth);
        bool p_can_declaration(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::declaration> p_match_declaration(size_t depth);
        bool m_returnstatement_semicolon_132(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth);
        bool m_expression_semicolon_133(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth);
        bool m_semicolon_134(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth);
        bool alternatives135(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth);
        bool p_can_statement(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::statement> p_match_statement(size_t depth);
        bool m_ident_136(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function_arg>& actual, yaoosl::parsing::instance::function_arg_state& state, size_t depth);
        bool p_can_function_arg(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::function_arg> p_match_function_arg(size_t depth);
        bool m_curlybrackedopen_137(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth);
        bool m_curlybrackedclose_138(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth);
        bool m_controlstructure_139(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth);
        bool m_statement_140(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth);
        bool alternatives141(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth);
        bool while142_143(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth);
        bool m_curlybrackedclose_144(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth);
        bool p_can_scope(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::scope> p_match_scope(size_t depth);
        bool m_curlybrackedopen_145(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_get_scope_set_scope_146(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_set_scope_get_scope_147(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_get_scope_148(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_set_scope_149(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool alternatives150(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_curlybrackedclose_151(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool p_can_scope_getset(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::scope_getset> p_match_scope_getset(size_t depth);
        bool m_func_ident_roundbrackedopen_152(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth);
        bool m_functionarg_153(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth);
        bool m_functionarg_154(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth);
        bool m_roundbrackedclose_155(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth);
        bool m_comma_functionarg_156(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth);
        bool while157_158(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth);
        bool if159_160(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth);
        bool m_roundbrackedclose_scope_161(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth);
        bool p_can_function(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::function> p_match_function(size_t depth);
        bool m_scope_162(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure_body>& actual, yaoosl::parsing::instance::control_structure_body_state& state, size_t depth);
        bool m_controlstructure_163(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure_body>& actual, yaoosl::parsing::instance::control_structure_body_state& state, size_t depth);
        bool m_statement_164(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure_body>& actual, yaoosl::parsing::instance::control_structure_body_state& state, size_t depth);
        bool alternatives165(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure_body>& actual, yaoosl::parsing::instance::control_structure_body_state& state, size_t depth);
        bool p_can_control_structure_body(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::control_structure_body> p_match_control_structure_body(size_t depth);
        bool m_while_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_166(bool is_can, std::shared_ptr<yaoosl::parsing::instance::while_loop>& actual, yaoosl::parsing::instance::while_loop_state& state, size_t depth);
        bool p_can_while_loop(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::while_loop> p_match_while_loop(size_t depth);
        bool m_if_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_167(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth);
        bool m_else_168(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth);
        bool m_else_controlstructurebody_169(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth);
        bool if170_171(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth);
        bool p_can_if_else(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::if_else> p_match_if_else(size_t depth);
        bool m_case_expvalue_colon_controlstructurebody_172(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_case>& actual, yaoosl::parsing::instance::switch_case_state& state, size_t depth);
        bool p_can_switch_case(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::switch_case> p_match_switch_case(size_t depth);
        bool m_switch_roundbrackedopen_expression_roundbrackedclose_173(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth);
        bool m_curlybrackedclose_174(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth);
        bool m_switchcase_175(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth);
        bool if176_177(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth);
        bool m_default_colon_controlstructurebody_178(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth);
        bool alternatives179(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth);
        bool while180_181(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth);
        bool m_curlybrackedclose_182(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth);
        bool p_can_switch_(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::switch_> p_match_switch_(size_t depth);
        bool m_function_183(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth);
        bool m_whileloop_184(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth);
        bool m_ifelse_185(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth);
        bool m_switch_186(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth);
        bool m_scope_187(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth);
        bool alternatives188(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth);
        bool p_can_control_structure(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::control_structure> p_match_control_structure(size_t depth);
        bool m_public_189(bool is_can, std::shared_ptr<yaoosl::parsing::instance::encapsulation>& actual, yaoosl::parsing::instance::encapsulation_state& state, size_t depth);
        bool m_local_190(bool is_can, std::shared_ptr<yaoosl::parsing::instance::encapsulation>& actual, yaoosl::parsing::instance::encapsulation_state& state, size_t depth);
        bool m_derived_191(bool is_can, std::shared_ptr<yaoosl::parsing::instance::encapsulation>& actual, yaoosl::parsing::instance::encapsulation_state& state, size_t depth);
        bool m_private_192(bool is_can, std::shared_ptr<yaoosl::parsing::instance::encapsulation>& actual, yaoosl::parsing::instance::encapsulation_state& state, size_t depth);
        bool alternatives193(bool is_can, std::shared_ptr<yaoosl::parsing::instance::encapsulation>& actual, yaoosl::parsing::instance::encapsulation_state& state, size_t depth);
        bool p_can_encapsulation(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::encapsulation> p_match_encapsulation(size_t depth);
        bool m_namespace_identnavigation_194(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool m_curlybrackedopen_195(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool m_curlybrackedclose_196(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool m_namespace_197(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool m_conversion_198(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool m_class_199(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool m_method_200(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool alternatives201(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool while202_203(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool m_curlybrackedclose_204(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool p_can_namespace_(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::namespace_> p_match_namespace_(size_t depth);
        bool m_encapsulation_class_ident_205(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_curlybrackedopen_206(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_curlybrackedclose_207(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_indexer_208(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_operatorbinaryoverload_209(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_operatorunaryoverload_210(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_conversion_211(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_class_212(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_constructor_213(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_destructor_214(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_copystructor_215(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_property_216(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_method_217(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool alternatives218(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool while219_220(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_curlybrackedclose_221(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool p_can_class_(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::class_> p_match_class_(size_t depth);
        bool m_typematch_ident_222(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item_with_default>& actual, yaoosl::parsing::instance::method_arglist_item_with_default_state& state, size_t depth);
        bool m_equal_223(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item_with_default>& actual, yaoosl::parsing::instance::method_arglist_item_with_default_state& state, size_t depth);
        bool m_equal_expvalue_224(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item_with_default>& actual, yaoosl::parsing::instance::method_arglist_item_with_default_state& state, size_t depth);
        bool if225_226(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item_with_default>& actual, yaoosl::parsing::instance::method_arglist_item_with_default_state& state, size_t depth);
        bool p_can_method_arglist_item_with_default(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::method_arglist_item_with_default> p_match_method_arglist_item_with_default(size_t depth);
        bool m_typematch_ident_227(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item>& actual, yaoosl::parsing::instance::method_arglist_item_state& state, size_t depth);
        bool p_can_method_arglist_item(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::method_arglist_item> p_match_method_arglist_item(size_t depth);
        bool m_roundbrackedopen_228(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool m_methodarglistitemwithdefault_229(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool m_methodarglistitemwithdefault_230(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool m_roundbrackedclose_231(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool m_comma_methodarglistitemwithdefault_232(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool alternatives233(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool while234_235(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool m_comma_236(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool m_comma_237(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool if238_239(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool if240_241(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool m_roundbrackedclose_242(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool p_can_method_arglist(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::method_arglist> p_match_method_arglist(size_t depth);
        bool m_squarebrackedopen_243(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth);
        bool m_methodarglistitem_244(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth);
        bool m_squarebrackedclose_245(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth);
        bool m_comma_methodarglistitem_246(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth);
        bool alternatives247(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth);
        bool while248_249(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth);
        bool m_comma_250(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth);
        bool m_comma_251(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth);
        bool if252_253(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth);
        bool m_squarebrackedclose_254(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer>& actual, yaoosl::parsing::instance::method_arglist_indexer_state& state, size_t depth);
        bool p_can_method_arglist_indexer(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::method_arglist_indexer> p_match_method_arglist_indexer(size_t depth);
        bool m_ident_255(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_ident>& actual, yaoosl::parsing::instance::method_ident_state& state, size_t depth);
        bool m_templatedefinition_256(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_ident>& actual, yaoosl::parsing::instance::method_ident_state& state, size_t depth);
        bool m_templatedefinition_257(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_ident>& actual, yaoosl::parsing::instance::method_ident_state& state, size_t depth);
        bool if258_259(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_ident>& actual, yaoosl::parsing::instance::method_ident_state& state, size_t depth);
        bool p_can_method_ident(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::method_ident> p_match_method_ident(size_t depth);
        bool m_encapsulation_260(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth);
        bool m_unbound_261(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth);
        bool m_unbound_262(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth);
        bool if263_264(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth);
        bool m_typematch_methodident_methodarglist_scope_265(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth);
        bool p_can_method(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::method> p_match_method(size_t depth);
        bool m_encapsulation_methodident_methodarglist_scope_266(bool is_can, std::shared_ptr<yaoosl::parsing::instance::constructor>& actual, yaoosl::parsing::instance::constructor_state& state, size_t depth);
        bool p_can_constructor(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::constructor> p_match_constructor(size_t depth);
        bool m_encapsulation_tilde_methodident_methodarglist_scope_267(bool is_can, std::shared_ptr<yaoosl::parsing::instance::destructor>& actual, yaoosl::parsing::instance::destructor_state& state, size_t depth);
        bool p_can_destructor(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::destructor> p_match_destructor(size_t depth);
        bool m_encapsulation_plus_methodident_methodarglist_268(bool is_can, std::shared_ptr<yaoosl::parsing::instance::copystructor>& actual, yaoosl::parsing::instance::copystructor_state& state, size_t depth);
        bool m_scope_269(bool is_can, std::shared_ptr<yaoosl::parsing::instance::copystructor>& actual, yaoosl::parsing::instance::copystructor_state& state, size_t depth);
        bool m_equal_delete_270(bool is_can, std::shared_ptr<yaoosl::parsing::instance::copystructor>& actual, yaoosl::parsing::instance::copystructor_state& state, size_t depth);
        bool alternatives271(bool is_can, std::shared_ptr<yaoosl::parsing::instance::copystructor>& actual, yaoosl::parsing::instance::copystructor_state& state, size_t depth);
        bool p_can_copystructor(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::copystructor> p_match_copystructor(size_t depth);
        bool m_encapsulation_unbound_conversion_typematch_272(bool is_can, std::shared_ptr<yaoosl::parsing::instance::conversion>& actual, yaoosl::parsing::instance::conversion_state& state, size_t depth);
        bool m_roundbrackedopen_typematch_ident_roundbrackedclose_273(bool is_can, std::shared_ptr<yaoosl::parsing::instance::conversion>& actual, yaoosl::parsing::instance::conversion_state& state, size_t depth);
        bool m_scope_274(bool is_can, std::shared_ptr<yaoosl::parsing::instance::conversion>& actual, yaoosl::parsing::instance::conversion_state& state, size_t depth);
        bool p_can_conversion(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::conversion> p_match_conversion(size_t depth);
        bool m_encapsulation_typematch_275(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth);
        bool m_templatedefinition_276(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth);
        bool m_templatedefinition_277(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth);
        bool if278_279(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth);
        bool m_methodarglistindexer_scopegetset_280(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth);
        bool p_can_indexer(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::indexer> p_match_indexer(size_t depth);
        bool m_encapsulation_unbound_typematch_operator_281(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_templatedefinition_282(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_templatedefinition_283(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool if284_285(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_roundbrackedopen_methodarglistitem_roundbrackedclose_286(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_plus_287(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_minus_288(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_star_289(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_slash_290(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_lessthenlessthenlessthen_291(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_lessthenlessthen_292(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_lessthenequal_293(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_lessthen_294(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_greaterthengreaterthengreaterthen_295(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_greaterthengreaterthen_296(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_greaterthenequal_297(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_greaterthen_298(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_verticalbarverticalbar_299(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_verticalbar_300(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_ampersandampersand_301(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_ampersand_302(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool alternatives303(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_roundbrackedopen_methodarglistitem_roundbrackedclose_304(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool m_scope_305(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload>& actual, yaoosl::parsing::instance::operator_binary_overload_state& state, size_t depth);
        bool p_can_operator_binary_overload(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::operator_binary_overload> p_match_operator_binary_overload(size_t depth);
        bool m_encapsulation_unbound_typematch_operator_306(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth);
        bool m_templatedefinition_307(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth);
        bool m_templatedefinition_308(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth);
        bool if309_310(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth);
        bool m_plus_311(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth);
        bool m_minus_312(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth);
        bool m_exclamation_313(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth);
        bool m_tilde_314(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth);
        bool alternatives315(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth);
        bool m_roundbrackedopen_methodarglistitem_roundbrackedclose_316(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth);
        bool m_scope_317(bool is_can, std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload>& actual, yaoosl::parsing::instance::operator_unary_overload_state& state, size_t depth);
        bool p_can_operator_unary_overload(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::operator_unary_overload> p_match_operator_unary_overload(size_t depth);
        bool m_encapsulation_typematch_ident_semicolon_318(bool is_can, std::shared_ptr<yaoosl::parsing::instance::property>& actual, yaoosl::parsing::instance::property_state& state, size_t depth);
        bool m_encapsulation_typematch_ident_scopegetset_319(bool is_can, std::shared_ptr<yaoosl::parsing::instance::property>& actual, yaoosl::parsing::instance::property_state& state, size_t depth);
        bool alternatives320(bool is_can, std::shared_ptr<yaoosl::parsing::instance::property>& actual, yaoosl::parsing::instance::property_state& state, size_t depth);
        bool p_can_property(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::property> p_match_property(size_t depth);
        bool m_namespace_321(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth);
        bool m_conversion_322(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth);
        bool m_class_323(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth);
        bool m_method_324(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth);
        bool alternatives325(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth);
        bool while326_327(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth);
        bool p_can_main(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::main> p_match_main(size_t depth);
        bool m_expchain_expchaincall_328(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain>& actual, yaoosl::parsing::instance::exp_chain_state& state, size_t depth);
        bool m_expchain_expchainaccess_329(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain>& actual, yaoosl::parsing::instance::exp_chain_state& state, size_t depth);
        bool m_expchain_expchainindexer_330(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain>& actual, yaoosl::parsing::instance::exp_chain_state& state, size_t depth);
        bool m_expchainstart_331(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain>& actual, yaoosl::parsing::instance::exp_chain_state& state, size_t depth);
        bool lr_can_exp_chain(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_chain> lr_match_exp_chain(size_t depth);
        bool m_identnavigation_dot_ident_332(bool is_can, std::shared_ptr<yaoosl::parsing::instance::ident_navigation>& actual, yaoosl::parsing::instance::ident_navigation_state& state, size_t depth);
        bool m_ident_333(bool is_can, std::shared_ptr<yaoosl::parsing::instance::ident_navigation>& actual, yaoosl::parsing::instance::ident_navigation_state& state, size_t depth);
        bool lr_can_ident_navigation(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::ident_navigation> lr_match_ident_navigation(size_t depth);
        bool m_typenavigation_dot_ident_templateusage_334(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_navigation>& actual, yaoosl::parsing::instance::type_navigation_state& state, size_t depth);
        bool m_typenavigation_dot_ident_335(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_navigation>& actual, yaoosl::parsing::instance::type_navigation_state& state, size_t depth);
        bool m_ident_336(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_navigation>& actual, yaoosl::parsing::instance::type_navigation_state& state, size_t depth);
        bool lr_can_type_navigation(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::type_navigation> lr_match_type_navigation(size_t depth);
        bool m_expbinary3_lessthenlessthen_expunary_337(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_binary_3>& actual, yaoosl::parsing::instance::exp_binary_3_state& state, size_t depth);
        bool m_expbinary3_greaterthengreaterthen_expunary_338(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_binary_3>& actual, yaoosl::parsing::instance::exp_binary_3_state& state, size_t depth);
        bool m_expbinary3_lessthenlessthenlessthen_expunary_339(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_binary_3>& actual, yaoosl::parsing::instance::exp_binary_3_state& state, size_t depth);
        bool m_expbinary3_greaterthengreaterthengreaterthen_expunary_340(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_binary_3>& actual, yaoosl::parsing::instance::exp_binary_3_state& state, size_t depth);
        bool m_expunary_341(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_binary_3>& actual, yaoosl::parsing::instance::exp_binary_3_state& state, size_t depth);
        bool lr_can_exp_binary_3(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_binary_3> lr_match_exp_binary_3(size_t depth);
        bool m_expbinary2_ampersand_expbinary3_342(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_binary_2>& actual, yaoosl::parsing::instance::exp_binary_2_state& state, size_t depth);
        bool m_expbinary3_343(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_binary_2>& actual, yaoosl::parsing::instance::exp_binary_2_state& state, size_t depth);
        bool lr_can_exp_binary_2(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_binary_2> lr_match_exp_binary_2(size_t depth);
        bool m_expbinary1_verticalbar_expbinary2_344(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_binary_1>& actual, yaoosl::parsing::instance::exp_binary_1_state& state, size_t depth);
        bool m_expbinary2_345(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_binary_1>& actual, yaoosl::parsing::instance::exp_binary_1_state& state, size_t depth);
        bool lr_can_exp_binary_1(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_binary_1> lr_match_exp_binary_1(size_t depth);
        bool m_exparithmetic2_slash_expbinary1_346(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state, size_t depth);
        bool m_exparithmetic2_star_expbinary1_347(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state, size_t depth);
        bool m_expbinary1_348(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state, size_t depth);
        bool lr_can_exp_arithmetic_2(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> lr_match_exp_arithmetic_2(size_t depth);
        bool m_exparithmetic1_plus_exparithmetic2_349(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state, size_t depth);
        bool m_exparithmetic1_minus_exparithmetic2_350(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state, size_t depth);
        bool m_exparithmetic2_351(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state, size_t depth);
        bool lr_can_exp_arithmetic_1(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> lr_match_exp_arithmetic_1(size_t depth);
        bool m_expcompare_lessthenequal_exparithmetic1_352(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth);
        bool m_expcompare_lessthen_exparithmetic1_353(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth);
        bool m_expcompare_greaterthenequal_exparithmetic1_354(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth);
        bool m_expcompare_greaterthen_exparithmetic1_355(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth);
        bool m_exparithmetic1_356(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth);
        bool lr_can_exp_compare(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_compare> lr_match_exp_compare(size_t depth);
        bool m_expequality_lessthenequal_expcompare_357(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth);
        bool m_expequality_lessthen_expcompare_358(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth);
        bool m_expequality_greaterthenequal_expcompare_359(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth);
        bool m_expequality_greaterthen_expcompare_360(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth);
        bool m_expcompare_361(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth);
        bool lr_can_exp_equality(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_equality> lr_match_exp_equality(size_t depth);
        bool m_expand_ampersandampersand_expequality_362(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and>& actual, yaoosl::parsing::instance::exp_and_state& state, size_t depth);
        bool m_expequality_363(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and>& actual, yaoosl::parsing::instance::exp_and_state& state, size_t depth);
        bool lr_can_exp_and(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_and> lr_match_exp_and(size_t depth);
        bool m_expor_verticalbarverticalbar_expand_364(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or>& actual, yaoosl::parsing::instance::exp_or_state& state, size_t depth);
        bool m_expequality_365(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or>& actual, yaoosl::parsing::instance::exp_or_state& state, size_t depth);
        bool lr_can_exp_or(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_or> lr_match_exp_or(size_t depth);
        bool m_expression_equal_expression_366(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expression>& actual, yaoosl::parsing::instance::expression_state& state, size_t depth);
        bool m_expression_equal_expression_367(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expression>& actual, yaoosl::parsing::instance::expression_state& state, size_t depth);
        bool m_expor_368(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expression>& actual, yaoosl::parsing::instance::expression_state& state, size_t depth);
        bool lr_can_expression(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::expression> lr_match_expression(size_t depth);
        void skip();
    protected:
        std::string_view m_contents;
        std::string m_file;
        size_t m_line;
        size_t m_column;
        size_t m_offset;
        virtual void report(std::string_view message, size_t depth);
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
            TRUE_,
            FALSE_,
            BOOLEAN,
            IDENT,
            STRING,
            _ROUND_BRACKED_OPEN,
            _ROUND_BRACKED_CLOSE,
            _COMMA,
            _LESS_THEN,
            _GREATER_THEN,
            _EQUAL,
            _SQUARE_BRACKED_OPEN,
            _SQUARE_BRACKED_CLOSE,
            _DOT,
            _TYPEOF,
            _NAMEOF,
            _EXCLAMATION,
            _TILDE,
            _LESS_THEN_LESS_THEN,
            _GREATER_THEN_GREATER_THEN,
            _LESS_THEN_LESS_THEN_LESS_THEN,
            _GREATER_THEN_GREATER_THEN_GREATER_THEN,
            _AMPERSAND,
            _VERTICAL_BAR,
            _LESS_THEN_EQUAL,
            _GREATER_THEN_EQUAL,
            _AMPERSAND_AMPERSAND,
            _VERTICAL_BAR_VERTICAL_BAR,
            _RETURN,
            _SEMICOLON,
            _CURLY_BRACKED_OPEN,
            _CURLY_BRACKED_CLOSE,
            _GET,
            _SET,
            _FUNC,
            _WHILE,
            _IF,
            _ELSE,
            _CASE,
            _COLON,
            _SWITCH,
            _DEFAULT,
            _PUBLIC,
            _LOCAL,
            _DERIVED,
            _PRIVATE,
            _NAMESPACE,
            _CLASS,
            _UNBOUND,
            _DELETE,
            _CONVERSION,
            _OPERATOR,
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
        class template_usage_item
        {
        public:
            token key;
        };
        class template_usage
        {
        public:
            std::vector<std::shared_ptr<template_usage_item>> items;
        };
        class template_definition_item
        {
        public:
            token key;
            std::shared_ptr<exp_value> value;
        };
        class template_definition
        {
        public:
            std::vector<std::shared_ptr<template_definition_item>> items;
        };
        class exp_chain_start
        {
        public:
            std::variant<std::shared_ptr<call>, token> part;
        };
        class exp_chain_indexer
        {
        };
        class exp_chain_access
        {
        public:
            token capture40;
        };
        class exp_chain_call
        {
        public:
            std::shared_ptr<call> capture42;
        };
        class type_match
        {
        public:
            std::optional<bool> is_array;
            std::shared_ptr<type_navigation> base;
            std::shared_ptr<exp_value> array_size;
        };
        class typeof
        {
        public:
            std::shared_ptr<type_match> value;
        };
        class nameof
        {
        public:
            std::shared_ptr<exp_or> value;
        };
        class string_literal
        {
        public:
            token prefix;
            token value;
            token postfix;
        };
        class exp_value
        {
        public:
            std::shared_ptr<typeof> type;
            std::shared_ptr<nameof> name;
            token float_;
            token bool_;
            std::shared_ptr<string_literal> string;
            token int_;
        };
        class exp_nullar
        {
        public:
            std::variant<std::shared_ptr<statement>, std::shared_ptr<declaration>, std::shared_ptr<exp_chain>, std::shared_ptr<exp_value>> value;
        };
        class exp_unary
        {
        public:
            token operator_;
            std::variant<std::shared_ptr<exp_unary>, std::shared_ptr<exp_nullar>> value;
        };
        class return_statement
        {
        public:
            std::shared_ptr<exp_or> value;
        };
        class declaration
        {
        public:
            std::shared_ptr<type_match> type;
            token name;
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
        class scope_getset
        {
        public:
            std::shared_ptr<scope> get;
            std::shared_ptr<scope> set;
        };
        class function
        {
        public:
            token name;
            std::vector<std::shared_ptr<function_arg>> args;
            std::shared_ptr<scope> body;
        };
        class control_structure_body
        {
        public:
            std::variant<std::shared_ptr<scope>, std::shared_ptr<control_structure>, std::shared_ptr<statement>> body;
        };
        class while_loop
        {
        public:
            std::shared_ptr<expression> condition;
            std::shared_ptr<control_structure_body> body;
        };
        class if_else
        {
        public:
            std::shared_ptr<expression> condition;
            std::shared_ptr<control_structure_body> if_body;
            std::shared_ptr<control_structure_body> else_body;
        };
        class switch_case
        {
        public:
            std::shared_ptr<exp_value> value;
            std::shared_ptr<control_structure_body> body;
        };
        class switch_
        {
        public:
            std::shared_ptr<expression> value;
            std::vector<std::shared_ptr<switch_case>> part;
            std::vector<std::shared_ptr<control_structure_body>> default_body;
        };
        class control_structure
        {
        public:
            std::variant<std::shared_ptr<function>, std::shared_ptr<while_loop>, std::shared_ptr<if_else>, std::shared_ptr<switch_>, std::shared_ptr<scope>> content;
        };
        class encapsulation
        {
        public:
            token tok;
        };
        class namespace_
        {
        public:
            std::shared_ptr<ident_navigation> name;
            std::vector<std::shared_ptr<namespace_>> namespaces;
            std::vector<std::shared_ptr<conversion>> conversions;
            std::vector<std::shared_ptr<class_>> classes;
            std::vector<std::shared_ptr<method>> methods;
        };
        class class_
        {
        public:
            std::shared_ptr<encapsulation> scope;
            token name;
            std::vector<std::shared_ptr<indexer>> indexers;
            std::vector<std::shared_ptr<operator_binary_overload>> operators_binary;
            std::vector<std::shared_ptr<operator_unary_overload>> operators_unary;
            std::vector<std::shared_ptr<conversion>> conversions;
            std::vector<std::shared_ptr<class_>> classes;
            std::vector<std::shared_ptr<constructor>> constructors;
            std::vector<std::shared_ptr<destructor>> destructors;
            std::vector<std::shared_ptr<copystructor>> copystructors;
            std::vector<std::shared_ptr<property>> properties;
            std::vector<std::shared_ptr<method>> methods;
        };
        class method_arglist_item_with_default
        {
        public:
            std::shared_ptr<type_match> type;
            token name;
            std::shared_ptr<exp_value> value;
        };
        class method_arglist_item
        {
        public:
            std::shared_ptr<type_match> type;
            token name;
        };
        class method_arglist
        {
        public:
            std::vector<std::shared_ptr<method_arglist_item_with_default>> args;
        };
        class method_arglist_indexer
        {
        public:
            std::vector<std::shared_ptr<method_arglist_item>> args;
        };
        class method_ident
        {
        public:
            token name;
            std::shared_ptr<template_definition> template_;
        };
        class method
        {
        public:
            std::optional<bool> is_static;
            std::shared_ptr<encapsulation> encaps;
            std::shared_ptr<type_match> return_type;
            std::shared_ptr<method_ident> ident;
            std::shared_ptr<method_arglist> arglist;
            std::shared_ptr<scope> body;
        };
        class constructor
        {
        public:
            std::shared_ptr<encapsulation> encaps;
            std::shared_ptr<method_ident> ident;
            std::shared_ptr<method_arglist> arglist;
            std::shared_ptr<scope> body;
        };
        class destructor
        {
        public:
            std::shared_ptr<encapsulation> encaps;
            std::shared_ptr<method_ident> ident;
            std::shared_ptr<method_arglist> arglist;
            std::shared_ptr<scope> body;
        };
        class copystructor
        {
        public:
            std::shared_ptr<encapsulation> encaps;
            std::shared_ptr<method_ident> ident;
            std::shared_ptr<method_arglist> arglist;
            std::shared_ptr<scope> body;
        };
        class conversion
        {
        public:
            std::shared_ptr<encapsulation> encaps;
            std::shared_ptr<type_match> target_type;
            std::shared_ptr<type_match> source_type;
            token name;
            std::shared_ptr<scope> body;
        };
        class indexer
        {
        public:
            std::shared_ptr<encapsulation> encaps;
            std::shared_ptr<type_match> target_type;
            std::shared_ptr<template_definition> template_;
            std::shared_ptr<method_arglist_indexer> arglist;
            std::shared_ptr<scope_getset> body;
        };
        class operator_binary_overload
        {
        public:
            std::shared_ptr<encapsulation> encaps;
            std::shared_ptr<type_match> target_type;
            std::shared_ptr<template_definition> template_;
            std::shared_ptr<method_arglist_item> left;
            token operator_;
            std::shared_ptr<method_arglist_item> right;
            std::shared_ptr<scope> body;
        };
        class operator_unary_overload
        {
        public:
            std::shared_ptr<encapsulation> encaps;
            std::shared_ptr<type_match> target_type;
            std::shared_ptr<template_definition> template_;
            token operator_;
            std::shared_ptr<method_arglist_item> right;
            std::shared_ptr<scope> body;
        };
        class property
        {
        public:
            std::shared_ptr<encapsulation> encaps;
            std::shared_ptr<type_match> target_type;
            token name;
            std::shared_ptr<scope_getset> body;
        };
        class main
        {
        public:
            std::vector<std::shared_ptr<namespace_>> namespaces;
            std::vector<std::shared_ptr<conversion>> conversions;
            std::vector<std::shared_ptr<class_>> classes;
            std::vector<std::shared_ptr<method>> methods;
        };
        class exp_chain
        {
        public:
            std::variant<std::shared_ptr<exp_chain>, std::shared_ptr<exp_chain_start>> left;
            std::variant<std::shared_ptr<exp_chain_call>, std::shared_ptr<exp_chain_access>, std::shared_ptr<exp_chain_indexer>> right;
        };
        class ident_navigation
        {
        public:
            std::variant<std::shared_ptr<ident_navigation>, token> left;
            token right;
        };
        class type_navigation
        {
        public:
            std::variant<std::shared_ptr<type_navigation>, token> left;
            token right;
            std::shared_ptr<template_usage> template_;
        };
        class exp_binary_3
        {
        public:
            std::variant<std::shared_ptr<exp_binary_3>, std::shared_ptr<exp_unary>> left;
            token operator_;
            std::shared_ptr<exp_unary> right;
        };
        class exp_binary_2
        {
        public:
            std::variant<std::shared_ptr<exp_binary_2>, std::shared_ptr<exp_binary_3>> left;
            token operator_;
            std::shared_ptr<exp_binary_3> right;
        };
        class exp_binary_1
        {
        public:
            std::variant<std::shared_ptr<exp_binary_1>, std::shared_ptr<exp_binary_2>> left;
            token operator_;
            std::shared_ptr<exp_binary_2> right;
        };
        class exp_arithmetic_2
        {
        public:
            std::variant<std::shared_ptr<exp_arithmetic_2>, std::shared_ptr<exp_binary_1>> left;
            token operator_;
            std::shared_ptr<exp_binary_1> right;
        };
        class exp_arithmetic_1
        {
        public:
            std::variant<std::shared_ptr<exp_arithmetic_1>, std::shared_ptr<exp_arithmetic_2>> left;
            token operator_;
            std::shared_ptr<exp_arithmetic_2> right;
        };
        class exp_compare
        {
        public:
            std::variant<std::shared_ptr<exp_compare>, std::shared_ptr<exp_arithmetic_1>> left;
            token operator_;
            std::shared_ptr<exp_arithmetic_1> right;
        };
        class exp_equality
        {
        public:
            std::variant<std::shared_ptr<exp_equality>, std::shared_ptr<exp_compare>> left;
            token operator_;
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
            std::shared_ptr<exp_and> right;
        };
        class expression
        {
        public:
            std::shared_ptr<expression> assign_to;
            std::variant<std::shared_ptr<expression>, std::shared_ptr<exp_or>> value;
        };
        class call_state
        {
        };
        class template_usage_item_state
        {
        };
        class template_usage_state
        {
        };
        class template_definition_item_state
        {
        };
        class template_definition_state
        {
        };
        class exp_chain_start_state
        {
        };
        class exp_chain_indexer_state
        {
        };
        class exp_chain_access_state
        {
        };
        class exp_chain_call_state
        {
        };
        class type_match_state
        {
        };
        class typeof_state
        {
        };
        class nameof_state
        {
        };
        class string_literal_state
        {
        };
        class exp_value_state
        {
        };
        class exp_nullar_state
        {
        };
        class exp_unary_state
        {
        };
        class return_statement_state
        {
        };
        class declaration_state
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
        class scope_getset_state
        {
        };
        class function_state
        {
        };
        class control_structure_body_state
        {
        };
        class while_loop_state
        {
        };
        class if_else_state
        {
        };
        class switch_case_state
        {
        };
        class switch__state
        {
        public:
            std::optional<bool> has_default;
        };
        class control_structure_state
        {
        };
        class encapsulation_state
        {
        };
        class namespace__state
        {
        };
        class class__state
        {
        };
        class method_arglist_item_with_default_state
        {
        };
        class method_arglist_item_state
        {
        };
        class method_arglist_state
        {
        };
        class method_arglist_indexer_state
        {
        };
        class method_ident_state
        {
        };
        class method_state
        {
        };
        class constructor_state
        {
        };
        class destructor_state
        {
        };
        class copystructor_state
        {
        };
        class conversion_state
        {
        };
        class indexer_state
        {
        };
        class operator_binary_overload_state
        {
        };
        class operator_unary_overload_state
        {
        };
        class property_state
        {
        };
        class main_state
        {
        };
        class exp_chain_state
        {
        };
        class ident_navigation_state
        {
        };
        class type_navigation_state
        {
        };
        class exp_binary_3_state
        {
        };
        class exp_binary_2_state
        {
        };
        class exp_binary_1_state
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
        class expression_state
        {
        };
        std::shared_ptr<yaoosl::parsing::instance::main> parse();
        std::vector<std::string> create_string_tree(std::shared_ptr<call> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<template_usage_item> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<template_usage> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<template_definition_item> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<template_definition> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_chain_start> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_chain_indexer> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_chain_access> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_chain_call> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<type_match> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<typeof> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<nameof> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<string_literal> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_value> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_nullar> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_unary> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<return_statement> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<declaration> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<statement> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<function_arg> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<scope> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<scope_getset> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<function> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<control_structure_body> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<while_loop> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<if_else> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<switch_case> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<switch_> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<control_structure> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<encapsulation> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<namespace_> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<class_> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<method_arglist_item_with_default> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<method_arglist_item> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<method_arglist> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<method_arglist_indexer> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<method_ident> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<method> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<constructor> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<destructor> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<copystructor> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<conversion> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<indexer> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<operator_binary_overload> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<operator_unary_overload> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<property> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<main> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_chain> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<ident_navigation> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<type_navigation> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_binary_3> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_binary_2> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_binary_1> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_arithmetic_2> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_arithmetic_1> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_compare> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_equality> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_and> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_or> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<expression> node, std::string_view contents);
    };
}
