#ifndef __tree_sitter__character_set__
#define __tree_sitter__character_set__

#include "rule.h"
#include <set>

namespace tree_sitter  {
    namespace rules {
        struct CharacterRange {
            char min;
            char max;
            
            CharacterRange(char);
            CharacterRange(char, char);
            
            int max_int() const;
            int min_int() const;

            bool operator==(const CharacterRange &) const;
            bool operator<(const CharacterRange &) const;
            bool is_adjacent(const CharacterRange &) const;
            
            void add_range(const CharacterRange &);
            
            std::string to_string() const;
        };
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::rules::CharacterRange> {
        size_t operator()(const tree_sitter::rules::CharacterRange &range) const {
            return (hash<char>()(range.min) ^ hash<char>()(range.max));
        }
    };
}

namespace tree_sitter  {
    namespace rules {
        class CharacterSet : public Rule {
        public:
            CharacterSet();
            CharacterSet(const std::set<CharacterRange> &ranges);
            CharacterSet(const std::set<CharacterRange> &ranges, bool);
            
            CharacterSet complement() const;
            void union_with(const CharacterSet &other);
            std::pair<CharacterSet, bool> most_compact_representation() const;
            
            bool operator==(const Rule& other) const;
            size_t hash_code() const;
            rule_ptr copy() const;
            std::string to_string() const;
            void accept(Visitor &visitor) const;
            
            std::set<CharacterRange> ranges;
        };
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::rules::CharacterSet> : hash<tree_sitter::rules::Rule> {};
}

#endif
