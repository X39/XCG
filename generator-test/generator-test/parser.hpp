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
        class typeof;
        class nameof;
        class exp_value;
        class exp_nullar;
        class return_statement;
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
        class method_arglist_item;
        class method_arglist;
        class method_arglist_non_empty;
        class method_ident;
        class method;
        class constructor;
        class destructor;
        class copystructor;
        class conversion;
        class indexer;
        class property;
        class main;
        class exp_chain;
        class ident_navigation;
        class type_navigation;
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
        class typeof_state;
        class nameof_state;
        class exp_value_state;
        class exp_nullar_state;
        class return_statement_state;
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
        class method_arglist_item_state;
        class method_arglist_state;
        class method_arglist_non_empty_state;
        class method_ident_state;
        class method_state;
        class constructor_state;
        class destructor_state;
        class copystructor_state;
        class conversion_state;
        class indexer_state;
        class property_state;
        class main_state;
        class exp_chain_state;
        class ident_navigation_state;
        class type_navigation_state;
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
        void skip();
        bool next();
        char current();
        std::optional<size_t> token_integer(size_t depth);
        std::optional<size_t> token_scalar(size_t depth);
        std::optional<size_t> token_slash(size_t depth);
        std::optional<size_t> token_star(size_t depth);
        std::optional<size_t> token_plus(size_t depth);
        std::optional<size_t> token_minus(size_t depth);
        std::optional<size_t> token_underscore(size_t depth);
        std::optional<size_t> token_true(size_t depth);
        std::optional<size_t> token_false(size_t depth);
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
        std::optional<size_t> token__less_then_equal(size_t depth);
        std::optional<size_t> token__greater_then_equal(size_t depth);
        std::optional<size_t> token__and(size_t depth);
        std::optional<size_t> token__or(size_t depth);
        std::optional<size_t> token__return(size_t depth);
        std::optional<size_t> token__auto_137(size_t depth);
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
        std::optional<size_t> token__tilde(size_t depth);
        std::optional<size_t> token__delete(size_t depth);
        std::optional<size_t> token__conversion(size_t depth);
        bool m_ident_roundbrackedopen_52(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool m_expression_53(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool m_expression_54(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool m_roundbrackedclose_55(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool m_comma_expression_56(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool m_comma_57(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool alternatives58(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool m_roundbrackedclose_55(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool while59_60(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool m_expression_53(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool if61_62(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool m_roundbrackedclose_63(bool is_can, std::shared_ptr<yaoosl::parsing::instance::call>& actual, yaoosl::parsing::instance::call_state& state, size_t depth);
        bool p_can_call(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::call> p_match_call(size_t depth);
        bool m_ident_64(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage_item>& actual, yaoosl::parsing::instance::template_usage_item_state& state, size_t depth);
        bool p_can_template_usage_item(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::template_usage_item> p_match_template_usage_item(size_t depth);
        bool m_lessthen_65(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth);
        bool m_templateusageitem_66(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth);
        bool m_comma_67(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth);
        bool m_comma_templateusageitem_68(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth);
        bool alternatives69(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth);
        bool m_comma_67(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth);
        bool while70_71(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth);
        bool m_greaterthen_72(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_usage>& actual, yaoosl::parsing::instance::template_usage_state& state, size_t depth);
        bool p_can_template_usage(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::template_usage> p_match_template_usage(size_t depth);
        bool m_ident_73(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition_item>& actual, yaoosl::parsing::instance::template_definition_item_state& state, size_t depth);
        bool m_equal_74(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition_item>& actual, yaoosl::parsing::instance::template_definition_item_state& state, size_t depth);
        bool m_equal_expvalue_75(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition_item>& actual, yaoosl::parsing::instance::template_definition_item_state& state, size_t depth);
        bool m_equal_74(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition_item>& actual, yaoosl::parsing::instance::template_definition_item_state& state, size_t depth);
        bool if76_77(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition_item>& actual, yaoosl::parsing::instance::template_definition_item_state& state, size_t depth);
        bool p_can_template_definition_item(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::template_definition_item> p_match_template_definition_item(size_t depth);
        bool m_lessthen_78(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth);
        bool m_templatedefinitionitem_79(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth);
        bool m_comma_80(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth);
        bool m_comma_templatedefinitionitem_81(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth);
        bool alternatives82(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth);
        bool m_comma_80(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth);
        bool while83_84(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth);
        bool m_greaterthen_85(bool is_can, std::shared_ptr<yaoosl::parsing::instance::template_definition>& actual, yaoosl::parsing::instance::template_definition_state& state, size_t depth);
        bool p_can_template_definition(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::template_definition> p_match_template_definition(size_t depth);
        bool m_ident_86(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_start>& actual, yaoosl::parsing::instance::exp_chain_start_state& state, size_t depth);
        bool m_call_87(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_start>& actual, yaoosl::parsing::instance::exp_chain_start_state& state, size_t depth);
        bool p_can_exp_chain_start(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_chain_start> p_match_exp_chain_start(size_t depth);
        bool m_squarebrackedopen_88(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_indexer>& actual, yaoosl::parsing::instance::exp_chain_indexer_state& state, size_t depth);
        bool m_squarebrackedclose_89(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_indexer>& actual, yaoosl::parsing::instance::exp_chain_indexer_state& state, size_t depth);
        bool p_can_exp_chain_indexer(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_chain_indexer> p_match_exp_chain_indexer(size_t depth);
        bool m_dot_ident_90(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_access>& actual, yaoosl::parsing::instance::exp_chain_access_state& state, size_t depth);
        bool p_can_exp_chain_access(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_chain_access> p_match_exp_chain_access(size_t depth);
        bool m_dot_call_91(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain_call>& actual, yaoosl::parsing::instance::exp_chain_call_state& state, size_t depth);
        bool p_can_exp_chain_call(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_chain_call> p_match_exp_chain_call(size_t depth);
        bool m_typeof_roundbrackedopen_typenavigation_roundbrackedclose_92(bool is_can, std::shared_ptr<yaoosl::parsing::instance::typeof>& actual, yaoosl::parsing::instance::typeof_state& state, size_t depth);
        bool p_can_typeof(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::typeof> p_match_typeof(size_t depth);
        bool m_nameof_roundbrackedopen_expor_roundbrackedclose_93(bool is_can, std::shared_ptr<yaoosl::parsing::instance::nameof>& actual, yaoosl::parsing::instance::nameof_state& state, size_t depth);
        bool p_can_nameof(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::nameof> p_match_nameof(size_t depth);
        bool m_typeof_94(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth);
        bool m_nameof_95(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth);
        bool m_scalar_96(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth);
        bool m_boolean_97(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth);
        bool m_string_98(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth);
        bool m_integer_99(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth);
        bool alternatives100(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_value>& actual, yaoosl::parsing::instance::exp_value_state& state, size_t depth);
        bool p_can_exp_value(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_value> p_match_exp_value(size_t depth);
        bool m_roundbrackedopen_statement_roundbrackedclose_101(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth);
        bool m_expchain_102(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth);
        bool m_call_103(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth);
        bool m_expvalue_104(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth);
        bool alternatives105(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_nullar>& actual, yaoosl::parsing::instance::exp_nullar_state& state, size_t depth);
        bool p_can_exp_nullar(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_nullar> p_match_exp_nullar(size_t depth);
        bool m_return_expor_106(bool is_can, std::shared_ptr<yaoosl::parsing::instance::return_statement>& actual, yaoosl::parsing::instance::return_statement_state& state, size_t depth);
        bool p_can_return_statement(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::return_statement> p_match_return_statement(size_t depth);
        bool m_returnstatement_auto137_107(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth);
        bool m_expression_auto137_108(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth);
        bool m_auto137_109(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth);
        bool alternatives110(bool is_can, std::shared_ptr<yaoosl::parsing::instance::statement>& actual, yaoosl::parsing::instance::statement_state& state, size_t depth);
        bool p_can_statement(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::statement> p_match_statement(size_t depth);
        bool m_ident_111(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function_arg>& actual, yaoosl::parsing::instance::function_arg_state& state, size_t depth);
        bool p_can_function_arg(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::function_arg> p_match_function_arg(size_t depth);
        bool m_curlybrackedopen_112(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth);
        bool m_curlybrackedclose_113(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth);
        bool m_controlstructure_114(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth);
        bool m_statement_115(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth);
        bool alternatives116(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth);
        bool m_curlybrackedclose_113(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth);
        bool while117_118(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth);
        bool m_curlybrackedclose_119(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope>& actual, yaoosl::parsing::instance::scope_state& state, size_t depth);
        bool p_can_scope(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::scope> p_match_scope(size_t depth);
        bool m_curlybrackedopen_120(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_curlybrackedopen_121(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_curlybrackedclose_122(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_controlstructure_123(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_statement_124(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool alternatives125(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_curlybrackedclose_122(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool while126_127(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_curlybrackedclose_128(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_get_129(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_curlybrackedopen_130(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_curlybrackedclose_131(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_controlstructure_132(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_statement_133(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool alternatives134(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_curlybrackedclose_131(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool while135_136(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_curlybrackedclose_137(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_set_138(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool alternatives139(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool m_curlybrackedclose_140(bool is_can, std::shared_ptr<yaoosl::parsing::instance::scope_getset>& actual, yaoosl::parsing::instance::scope_getset_state& state, size_t depth);
        bool p_can_scope_getset(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::scope_getset> p_match_scope_getset(size_t depth);
        bool m_func_ident_roundbrackedopen_141(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth);
        bool m_functionarg_142(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth);
        bool m_functionarg_143(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth);
        bool m_roundbrackedclose_144(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth);
        bool m_comma_functionarg_145(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth);
        bool m_roundbrackedclose_144(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth);
        bool while146_147(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth);
        bool m_functionarg_142(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth);
        bool if148_149(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth);
        bool m_roundbrackedclose_scope_150(bool is_can, std::shared_ptr<yaoosl::parsing::instance::function>& actual, yaoosl::parsing::instance::function_state& state, size_t depth);
        bool p_can_function(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::function> p_match_function(size_t depth);
        bool m_scope_151(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure_body>& actual, yaoosl::parsing::instance::control_structure_body_state& state, size_t depth);
        bool m_controlstructure_152(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure_body>& actual, yaoosl::parsing::instance::control_structure_body_state& state, size_t depth);
        bool m_statement_153(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure_body>& actual, yaoosl::parsing::instance::control_structure_body_state& state, size_t depth);
        bool alternatives154(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure_body>& actual, yaoosl::parsing::instance::control_structure_body_state& state, size_t depth);
        bool p_can_control_structure_body(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::control_structure_body> p_match_control_structure_body(size_t depth);
        bool m_while_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_155(bool is_can, std::shared_ptr<yaoosl::parsing::instance::while_loop>& actual, yaoosl::parsing::instance::while_loop_state& state, size_t depth);
        bool p_can_while_loop(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::while_loop> p_match_while_loop(size_t depth);
        bool m_if_roundbrackedopen_expression_roundbrackedclose_controlstructurebody_156(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth);
        bool m_else_157(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth);
        bool m_else_controlstructurebody_158(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth);
        bool m_else_157(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth);
        bool if159_160(bool is_can, std::shared_ptr<yaoosl::parsing::instance::if_else>& actual, yaoosl::parsing::instance::if_else_state& state, size_t depth);
        bool p_can_if_else(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::if_else> p_match_if_else(size_t depth);
        bool m_case_expvalue_colon_controlstructurebody_161(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_case>& actual, yaoosl::parsing::instance::switch_case_state& state, size_t depth);
        bool p_can_switch_case(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::switch_case> p_match_switch_case(size_t depth);
        bool m_switch_roundbrackedopen_expression_roundbrackedclose_162(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth);
        bool m_curlybrackedclose_163(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth);
        bool m_switchcase_164(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth);
        bool if165_166(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth);
        bool m_default_colon_controlstructurebody_167(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth);
        bool alternatives168(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth);
        bool m_curlybrackedclose_163(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth);
        bool while169_170(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth);
        bool m_curlybrackedclose_171(bool is_can, std::shared_ptr<yaoosl::parsing::instance::switch_>& actual, yaoosl::parsing::instance::switch__state& state, size_t depth);
        bool p_can_switch_(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::switch_> p_match_switch_(size_t depth);
        bool m_function_172(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth);
        bool m_whileloop_173(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth);
        bool m_ifelse_174(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth);
        bool m_switch_175(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth);
        bool m_scope_176(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth);
        bool alternatives177(bool is_can, std::shared_ptr<yaoosl::parsing::instance::control_structure>& actual, yaoosl::parsing::instance::control_structure_state& state, size_t depth);
        bool p_can_control_structure(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::control_structure> p_match_control_structure(size_t depth);
        bool m_public_178(bool is_can, std::shared_ptr<yaoosl::parsing::instance::encapsulation>& actual, yaoosl::parsing::instance::encapsulation_state& state, size_t depth);
        bool m_local_179(bool is_can, std::shared_ptr<yaoosl::parsing::instance::encapsulation>& actual, yaoosl::parsing::instance::encapsulation_state& state, size_t depth);
        bool m_derived_180(bool is_can, std::shared_ptr<yaoosl::parsing::instance::encapsulation>& actual, yaoosl::parsing::instance::encapsulation_state& state, size_t depth);
        bool m_private_181(bool is_can, std::shared_ptr<yaoosl::parsing::instance::encapsulation>& actual, yaoosl::parsing::instance::encapsulation_state& state, size_t depth);
        bool alternatives182(bool is_can, std::shared_ptr<yaoosl::parsing::instance::encapsulation>& actual, yaoosl::parsing::instance::encapsulation_state& state, size_t depth);
        bool p_can_encapsulation(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::encapsulation> p_match_encapsulation(size_t depth);
        bool m_namespace_identnavigation_183(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool m_curlybrackedopen_184(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool m_curlybrackedclose_185(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool m_namespace_186(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool m_conversion_187(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool m_class_188(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool m_method_189(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool alternatives190(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool m_curlybrackedclose_185(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool while191_192(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool m_curlybrackedclose_193(bool is_can, std::shared_ptr<yaoosl::parsing::instance::namespace_>& actual, yaoosl::parsing::instance::namespace__state& state, size_t depth);
        bool p_can_namespace_(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::namespace_> p_match_namespace_(size_t depth);
        bool m_encapsulation_class_ident_194(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_curlybrackedopen_195(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_curlybrackedclose_196(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_conversion_197(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_class_198(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_constructor_199(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_destructor_200(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_copystructor_201(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_method_202(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_property_203(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_indexer_204(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool alternatives205(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_curlybrackedclose_196(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool while206_207(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool m_curlybrackedclose_208(bool is_can, std::shared_ptr<yaoosl::parsing::instance::class_>& actual, yaoosl::parsing::instance::class__state& state, size_t depth);
        bool p_can_class_(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::class_> p_match_class_(size_t depth);
        bool m_typenavigation_ident_209(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item>& actual, yaoosl::parsing::instance::method_arglist_item_state& state, size_t depth);
        bool m_equal_210(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item>& actual, yaoosl::parsing::instance::method_arglist_item_state& state, size_t depth);
        bool m_equal_expvalue_211(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item>& actual, yaoosl::parsing::instance::method_arglist_item_state& state, size_t depth);
        bool m_equal_210(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item>& actual, yaoosl::parsing::instance::method_arglist_item_state& state, size_t depth);
        bool if212_213(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_item>& actual, yaoosl::parsing::instance::method_arglist_item_state& state, size_t depth);
        bool p_can_method_arglist_item(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::method_arglist_item> p_match_method_arglist_item(size_t depth);
        bool m_roundbrackedopen_214(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool m_methodarglistitem_215(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool m_methodarglistitem_216(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool m_roundbrackedclose_217(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool m_comma_methodarglistitem_218(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool alternatives219(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool m_roundbrackedclose_217(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool while220_221(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool m_comma_222(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool m_comma_223(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool m_comma_222(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool if224_225(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool m_methodarglistitem_215(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool if226_227(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool m_roundbrackedclose_228(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist>& actual, yaoosl::parsing::instance::method_arglist_state& state, size_t depth);
        bool p_can_method_arglist(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::method_arglist> p_match_method_arglist(size_t depth);
        bool m_roundbrackedopen_229(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth);
        bool m_methodarglistitem_230(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth);
        bool m_roundbrackedclose_231(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth);
        bool m_comma_methodarglistitem_232(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth);
        bool alternatives233(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth);
        bool m_roundbrackedclose_231(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth);
        bool while234_235(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth);
        bool m_comma_236(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth);
        bool m_comma_237(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth);
        bool m_comma_236(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth);
        bool if238_239(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth);
        bool m_roundbrackedclose_240(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty>& actual, yaoosl::parsing::instance::method_arglist_non_empty_state& state, size_t depth);
        bool p_can_method_arglist_non_empty(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::method_arglist_non_empty> p_match_method_arglist_non_empty(size_t depth);
        bool m_ident_241(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_ident>& actual, yaoosl::parsing::instance::method_ident_state& state, size_t depth);
        bool m_templatedefinition_242(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_ident>& actual, yaoosl::parsing::instance::method_ident_state& state, size_t depth);
        bool m_templatedefinition_243(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_ident>& actual, yaoosl::parsing::instance::method_ident_state& state, size_t depth);
        bool m_templatedefinition_242(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_ident>& actual, yaoosl::parsing::instance::method_ident_state& state, size_t depth);
        bool if244_245(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method_ident>& actual, yaoosl::parsing::instance::method_ident_state& state, size_t depth);
        bool p_can_method_ident(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::method_ident> p_match_method_ident(size_t depth);
        bool m_encapsulation_246(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth);
        bool m_unbound_247(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth);
        bool m_unbound_248(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth);
        bool m_unbound_247(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth);
        bool if249_250(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth);
        bool m_typenavigation_methodident_methodarglist_scope_251(bool is_can, std::shared_ptr<yaoosl::parsing::instance::method>& actual, yaoosl::parsing::instance::method_state& state, size_t depth);
        bool p_can_method(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::method> p_match_method(size_t depth);
        bool m_encapsulation_typenavigation_methodident_methodarglist_scope_252(bool is_can, std::shared_ptr<yaoosl::parsing::instance::constructor>& actual, yaoosl::parsing::instance::constructor_state& state, size_t depth);
        bool p_can_constructor(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::constructor> p_match_constructor(size_t depth);
        bool m_encapsulation_typenavigation_tilde_methodident_methodarglist_scope_253(bool is_can, std::shared_ptr<yaoosl::parsing::instance::destructor>& actual, yaoosl::parsing::instance::destructor_state& state, size_t depth);
        bool p_can_destructor(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::destructor> p_match_destructor(size_t depth);
        bool m_encapsulation_typenavigation_plus_methodident_methodarglist_254(bool is_can, std::shared_ptr<yaoosl::parsing::instance::copystructor>& actual, yaoosl::parsing::instance::copystructor_state& state, size_t depth);
        bool m_scope_255(bool is_can, std::shared_ptr<yaoosl::parsing::instance::copystructor>& actual, yaoosl::parsing::instance::copystructor_state& state, size_t depth);
        bool m_equal_delete_256(bool is_can, std::shared_ptr<yaoosl::parsing::instance::copystructor>& actual, yaoosl::parsing::instance::copystructor_state& state, size_t depth);
        bool alternatives257(bool is_can, std::shared_ptr<yaoosl::parsing::instance::copystructor>& actual, yaoosl::parsing::instance::copystructor_state& state, size_t depth);
        bool p_can_copystructor(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::copystructor> p_match_copystructor(size_t depth);
        bool m_encapsulation_conversion_typenavigation_roundbrackedopen_typenavigation_ident_roundbrackedclose_scope_258(bool is_can, std::shared_ptr<yaoosl::parsing::instance::conversion>& actual, yaoosl::parsing::instance::conversion_state& state, size_t depth);
        bool p_can_conversion(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::conversion> p_match_conversion(size_t depth);
        bool m_encapsulation_typenavigation_259(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth);
        bool m_templatedefinition_260(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth);
        bool m_templatedefinition_261(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth);
        bool m_templatedefinition_260(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth);
        bool if262_263(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth);
        bool m_squarebrackedopen_methodarglistnonempty_squarebrackedclose_scopegetset_264(bool is_can, std::shared_ptr<yaoosl::parsing::instance::indexer>& actual, yaoosl::parsing::instance::indexer_state& state, size_t depth);
        bool p_can_indexer(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::indexer> p_match_indexer(size_t depth);
        bool m_encapsulation_typenavigation_ident_auto137_265(bool is_can, std::shared_ptr<yaoosl::parsing::instance::property>& actual, yaoosl::parsing::instance::property_state& state, size_t depth);
        bool m_encapsulation_typenavigation_ident_scopegetset_266(bool is_can, std::shared_ptr<yaoosl::parsing::instance::property>& actual, yaoosl::parsing::instance::property_state& state, size_t depth);
        bool alternatives267(bool is_can, std::shared_ptr<yaoosl::parsing::instance::property>& actual, yaoosl::parsing::instance::property_state& state, size_t depth);
        bool p_can_property(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::property> p_match_property(size_t depth);
        bool m_namespace_268(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth);
        bool m_conversion_269(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth);
        bool m_class_270(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth);
        bool m_method_271(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth);
        bool alternatives272(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth);
        bool while273_274(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main>& actual, yaoosl::parsing::instance::main_state& state, size_t depth);
        bool p_can_main(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::main> p_match_main(size_t depth);
        bool m_expchain_expchaincall_275(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain>& actual, yaoosl::parsing::instance::exp_chain_state& state, size_t depth);
        bool m_expchain_expchainaccess_276(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain>& actual, yaoosl::parsing::instance::exp_chain_state& state, size_t depth);
        bool m_expchain_expchainindexer_277(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain>& actual, yaoosl::parsing::instance::exp_chain_state& state, size_t depth);
        bool m_expchainstart_278(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_chain>& actual, yaoosl::parsing::instance::exp_chain_state& state, size_t depth);
        bool lr_can_exp_chain(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_chain> lr_match_exp_chain(size_t depth);
        bool m_identnavigation_dot_ident_279(bool is_can, std::shared_ptr<yaoosl::parsing::instance::ident_navigation>& actual, yaoosl::parsing::instance::ident_navigation_state& state, size_t depth);
        bool m_ident_280(bool is_can, std::shared_ptr<yaoosl::parsing::instance::ident_navigation>& actual, yaoosl::parsing::instance::ident_navigation_state& state, size_t depth);
        bool lr_can_ident_navigation(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::ident_navigation> lr_match_ident_navigation(size_t depth);
        bool m_typenavigation_dot_ident_templateusage_281(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_navigation>& actual, yaoosl::parsing::instance::type_navigation_state& state, size_t depth);
        bool m_typenavigation_dot_ident_282(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_navigation>& actual, yaoosl::parsing::instance::type_navigation_state& state, size_t depth);
        bool m_ident_283(bool is_can, std::shared_ptr<yaoosl::parsing::instance::type_navigation>& actual, yaoosl::parsing::instance::type_navigation_state& state, size_t depth);
        bool lr_can_type_navigation(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::type_navigation> lr_match_type_navigation(size_t depth);
        bool m_exparithmetic2_slash_expnullar_284(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state, size_t depth);
        bool m_exparithmetic2_star_expnullar_285(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state, size_t depth);
        bool m_expnullar_286(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2>& actual, yaoosl::parsing::instance::exp_arithmetic_2_state& state, size_t depth);
        bool lr_can_exp_arithmetic_2(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_2> lr_match_exp_arithmetic_2(size_t depth);
        bool m_exparithmetic1_plus_exparithmetic2_287(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state, size_t depth);
        bool m_exparithmetic1_minus_exparithmetic2_288(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state, size_t depth);
        bool m_exparithmetic2_289(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1>& actual, yaoosl::parsing::instance::exp_arithmetic_1_state& state, size_t depth);
        bool lr_can_exp_arithmetic_1(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_arithmetic_1> lr_match_exp_arithmetic_1(size_t depth);
        bool m_expcompare_lessthenequal_exparithmetic1_290(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth);
        bool m_expcompare_lessthen_exparithmetic1_291(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth);
        bool m_expcompare_greaterthenequal_exparithmetic1_292(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth);
        bool m_expcompare_greaterthen_exparithmetic1_293(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth);
        bool m_exparithmetic1_294(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_compare>& actual, yaoosl::parsing::instance::exp_compare_state& state, size_t depth);
        bool lr_can_exp_compare(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_compare> lr_match_exp_compare(size_t depth);
        bool m_expequality_lessthenequal_expcompare_295(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth);
        bool m_expequality_lessthen_expcompare_296(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth);
        bool m_expequality_greaterthenequal_expcompare_297(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth);
        bool m_expequality_greaterthen_expcompare_298(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth);
        bool m_expcompare_299(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_equality>& actual, yaoosl::parsing::instance::exp_equality_state& state, size_t depth);
        bool lr_can_exp_equality(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_equality> lr_match_exp_equality(size_t depth);
        bool m_expand_and_expequality_300(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and>& actual, yaoosl::parsing::instance::exp_and_state& state, size_t depth);
        bool m_expequality_301(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_and>& actual, yaoosl::parsing::instance::exp_and_state& state, size_t depth);
        bool lr_can_exp_and(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_and> lr_match_exp_and(size_t depth);
        bool m_expor_or_expand_302(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or>& actual, yaoosl::parsing::instance::exp_or_state& state, size_t depth);
        bool m_expequality_303(bool is_can, std::shared_ptr<yaoosl::parsing::instance::exp_or>& actual, yaoosl::parsing::instance::exp_or_state& state, size_t depth);
        bool lr_can_exp_or(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::exp_or> lr_match_exp_or(size_t depth);
        bool m_expression_equal_expression_304(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expression>& actual, yaoosl::parsing::instance::expression_state& state, size_t depth);
        bool m_expor_305(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expression>& actual, yaoosl::parsing::instance::expression_state& state, size_t depth);
        bool lr_can_expression(size_t depth);
        std::shared_ptr<yaoosl::parsing::instance::expression> lr_match_expression(size_t depth);
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
            TRUE,
            FALSE,
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
            _LESS_THEN_EQUAL,
            _GREATER_THEN_EQUAL,
            _AND,
            _OR,
            _RETURN,
            _AUTO_137,
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
            _TILDE,
            _DELETE,
            _CONVERSION,
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
            std::variant<token, std::shared_ptr<call>> part;
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
        class typeof
        {
        public:
            std::shared_ptr<type_navigation> value;
        };
        class nameof
        {
        public:
            std::shared_ptr<exp_or> value;
        };
        class exp_value
        {
        public:
            std::variant<std::shared_ptr<typeof>, std::shared_ptr<nameof>, token> value;
        };
        class exp_nullar
        {
        public:
            std::variant<std::shared_ptr<statement>, std::shared_ptr<exp_chain>, std::shared_ptr<call>, std::shared_ptr<exp_value>> value;
        };
        class return_statement
        {
        public:
            std::shared_ptr<exp_or> value;
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
            std::vector<std::variant<std::shared_ptr<control_structure>, std::shared_ptr<statement>>> get_body;
            std::vector<std::variant<std::shared_ptr<control_structure>, std::shared_ptr<statement>>> set_body;
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
        };
        class namespace_
        {
        public:
            std::shared_ptr<ident_navigation> name;
            std::vector<std::variant<std::shared_ptr<namespace_>, std::shared_ptr<conversion>, std::shared_ptr<class_>, std::shared_ptr<method>>> contents;
        };
        class class_
        {
        public:
            std::shared_ptr<encapsulation> scope;
            token name;
            std::vector<std::variant<std::shared_ptr<conversion>, std::shared_ptr<class_>, std::shared_ptr<constructor>, std::shared_ptr<destructor>, std::shared_ptr<copystructor>, std::shared_ptr<method>, std::shared_ptr<property>, std::shared_ptr<indexer>>> contents;
        };
        class method_arglist_item
        {
        public:
            std::shared_ptr<type_navigation> type;
            token name;
            std::shared_ptr<exp_value> value;
        };
        class method_arglist
        {
        public:
            std::vector<std::shared_ptr<method_arglist_item>> args;
        };
        class method_arglist_non_empty
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
            std::shared_ptr<type_navigation> return_type;
            std::shared_ptr<method_ident> ident;
            std::shared_ptr<method_arglist> arglist;
            std::shared_ptr<scope> body;
        };
        class constructor
        {
        public:
            std::shared_ptr<encapsulation> encaps;
            std::shared_ptr<type_navigation> return_type;
            std::shared_ptr<method_ident> ident;
            std::shared_ptr<method_arglist> arglist;
            std::shared_ptr<scope> body;
        };
        class destructor
        {
        public:
            std::shared_ptr<encapsulation> encaps;
            std::shared_ptr<type_navigation> return_type;
            std::shared_ptr<method_ident> ident;
            std::shared_ptr<method_arglist> arglist;
            std::shared_ptr<scope> body;
        };
        class copystructor
        {
        public:
            std::shared_ptr<encapsulation> encaps;
            std::shared_ptr<type_navigation> return_type;
            std::shared_ptr<method_ident> ident;
            std::shared_ptr<method_arglist> arglist;
            std::shared_ptr<scope> body;
        };
        class conversion
        {
        public:
            std::shared_ptr<encapsulation> encaps;
            std::shared_ptr<type_navigation> target_type;
            std::shared_ptr<type_navigation> source_type;
            token name;
            std::shared_ptr<scope> body;
        };
        class indexer
        {
        public:
            std::shared_ptr<encapsulation> encaps;
            std::shared_ptr<type_navigation> target_type;
            std::shared_ptr<template_definition> template_;
            std::shared_ptr<method_arglist_non_empty> arglist;
            std::shared_ptr<scope_getset> body;
        };
        class property
        {
        public:
            std::shared_ptr<encapsulation> encaps;
            std::shared_ptr<type_navigation> target_type;
            token name;
            std::shared_ptr<scope_getset> body;
        };
        class main
        {
        public:
            std::vector<std::variant<std::shared_ptr<namespace_>, std::shared_ptr<conversion>, std::shared_ptr<class_>, std::shared_ptr<method>>> contents;
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
        class typeof_state
        {
        };
        class nameof_state
        {
        };
        class exp_value_state
        {
        };
        class exp_nullar_state
        {
        };
        class return_statement_state
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
        class method_arglist_item_state
        {
        };
        class method_arglist_state
        {
        };
        class method_arglist_non_empty_state
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
        std::vector<std::string> create_string_tree(std::shared_ptr<typeof> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<nameof> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_value> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_nullar> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<return_statement> node, std::string_view contents);
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
        std::vector<std::string> create_string_tree(std::shared_ptr<method_arglist_item> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<method_arglist> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<method_arglist_non_empty> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<method_ident> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<method> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<constructor> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<destructor> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<copystructor> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<conversion> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<indexer> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<property> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<main> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_chain> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<ident_navigation> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<type_navigation> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_arithmetic_2> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_arithmetic_1> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_compare> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_equality> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_and> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<exp_or> node, std::string_view contents);
        std::vector<std::string> create_string_tree(std::shared_ptr<expression> node, std::string_view contents);
    };
}
