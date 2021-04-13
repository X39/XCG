#include <memory>
#include <string>
#include <string_view>
#include <optional>
#include <variant>

namespace yaoosl::parsing
{
    class instance
    {
    private:
        class resetable;
    public:
        class token;
        class p_expc;
        class p_main;
        class lr_expb;
        class lr_expa;
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
        std::optional<size_t> token__auto_3();
        std::optional<size_t> token__auto_5();
        std::optional<size_t> token__auto_9();
        std::optional<size_t> token__auto_12();
        std::optional<size_t> token__auto_16();
        std::optional<size_t> token__auto_19();
        bool auto3_expA_auto5_18(bool is_can, std::shared_ptr<yaoosl::parsing::instance::p_expc> actual);
        bool scalar_23(bool is_can, std::shared_ptr<yaoosl::parsing::instance::p_expc> actual);
        bool integer_26(bool is_can, std::shared_ptr<yaoosl::parsing::instance::p_expc> actual);
        bool alternatives28(bool is_can, std::shared_ptr<yaoosl::parsing::instance::p_expc> actual);
        bool p_can_expc();
        std::shared_ptr<yaoosl::parsing::instance::p_expc> p_match_expc();
        bool expA_32(bool is_can, std::shared_ptr<yaoosl::parsing::instance::p_main> actual);
        bool p_can_main();
        std::shared_ptr<yaoosl::parsing::instance::p_main> p_match_main();
        bool expB_auto9_expC_36(bool is_can, std::shared_ptr<yaoosl::parsing::instance::lr_expb> actual);
        bool expB_auto12_expC_41(bool is_can, std::shared_ptr<yaoosl::parsing::instance::lr_expb> actual);
        bool expC_46(bool is_can, std::shared_ptr<yaoosl::parsing::instance::lr_expb> actual);
        bool lr_can_expb();
        std::shared_ptr<yaoosl::parsing::instance::lr_expb> lr_match_expb();
        bool expA_auto16_expB_50(bool is_can, std::shared_ptr<yaoosl::parsing::instance::lr_expa> actual);
        bool expA_auto19_expB_55(bool is_can, std::shared_ptr<yaoosl::parsing::instance::lr_expa> actual);
        bool expB_60(bool is_can, std::shared_ptr<yaoosl::parsing::instance::lr_expa> actual);
        bool lr_can_expa();
        std::shared_ptr<yaoosl::parsing::instance::lr_expa> lr_match_expa();
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
        enum tok
        {
            INTEGER,
            SCALAR,
            _AUTO_3,
            _AUTO_5,
            _AUTO_9,
            _AUTO_12,
            _AUTO_16,
            _AUTO_19,
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
        class p_expc
        {
        public:
            std::variant<std::shared_ptr<lr_expa>, token> value;
        };
        class p_main
        {
        public:
            std::shared_ptr<lr_expa> root;
        };
        class lr_expb
        {
        public:
            char op;
            std::variant<std::shared_ptr<lr_expb>, std::shared_ptr<p_expc>> left;
            std::shared_ptr<p_expc> right;
        };
        class lr_expa
        {
        public:
            char op;
            std::variant<std::shared_ptr<lr_expa>, std::shared_ptr<lr_expb>> left;
            std::shared_ptr<lr_expb> right;
        };
        std::shared_ptr<yaoosl::parsing::instance::p_main> parse();
    };
}
