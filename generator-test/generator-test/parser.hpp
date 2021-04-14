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
        class expc;
        class main;
        class expb;
        class expa;
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
        std::optional<size_t> token_roundo();
        std::optional<size_t> token_roundc();
        std::optional<size_t> token_slash();
        std::optional<size_t> token_star();
        std::optional<size_t> token_plus();
        std::optional<size_t> token_minus();
        bool m_roundO_expA_roundC_9(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expc> actual);
        bool m_scalar_10(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expc> actual);
        bool m_integer_11(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expc> actual);
        bool alternatives12(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expc> actual);
        bool p_can_expc();
        std::shared_ptr<yaoosl::parsing::instance::expc> p_match_expc();
        bool m_expA_13(bool is_can, std::shared_ptr<yaoosl::parsing::instance::main> actual);
        bool p_can_main();
        std::shared_ptr<yaoosl::parsing::instance::main> p_match_main();
        bool m_expB_slash_expC_14(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expb> actual);
        bool m_expB_star_expC_15(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expb> actual);
        bool m_expC_16(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expb> actual);
        bool lr_can_expb();
        std::shared_ptr<yaoosl::parsing::instance::expb> lr_match_expb();
        bool m_expA_plus_expB_17(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expa> actual);
        bool m_expA_minus_expB_18(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expa> actual);
        bool m_expB_19(bool is_can, std::shared_ptr<yaoosl::parsing::instance::expa> actual);
        bool lr_can_expa();
        std::shared_ptr<yaoosl::parsing::instance::expa> lr_match_expa();
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
            ROUNDO,
            ROUNDC,
            SLASH,
            STAR,
            PLUS,
            MINUS,
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
        class expc
        {
        public:
            std::variant<std::shared_ptr<expa>, token> value;
        };
        class main
        {
        public:
            std::shared_ptr<expa> root;
        };
        class expb
        {
        public:
            std::optional<char> op;
            std::variant<std::shared_ptr<expb>, std::shared_ptr<expc>> left;
            std::shared_ptr<expc> right;
        };
        class expa
        {
        public:
            std::optional<char> op;
            std::variant<std::shared_ptr<expa>, std::shared_ptr<expb>> left;
            std::shared_ptr<expb> right;
        };
        void print_tree(std::shared_ptr<expc> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<main> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<expb> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        void print_tree(std::shared_ptr<expa> node, std::vector<char> v, std::string_view& contents, std::stringstream& sstream);
        std::shared_ptr<yaoosl::parsing::instance::main> parse();
    };
}
