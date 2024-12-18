#include <tao/pegtl.hpp>
#include <iostream>

#include "attribute.hpp"
#include "basic_components.hpp"
#include "class.hpp"
#include "function.hpp"
#include "member.hpp"
#include "state.hpp"
#include "post_process.hpp"
#include "preprocessor.hpp"

using namespace tao::pegtl;

namespace broma {
	/// @brief Broma's top-level grammar.
	struct root_grammar : until<eof, sep, must<sor<include_expr, seq<opt<attribute>, sor<class_statement, function>>>>, sep> {};

	Root parse_file(std::string const& fname) {
		file_input<> input(fname);

		Root root;
		ScratchData scratch;
		parse<must<root_grammar>, run_action>(input, &root, &scratch);
		post_process(root);

		if (scratch.errors.size()) {
			std::cerr << "[Broma] errors found on parsing: \n";

			for (auto& e : scratch.errors) {
				std::cerr << "\t" << e.what() << "\n";
			}

			std::exit(1);
		}

		return root;
	}
	SafeRootResult parse_file_safely(std::string const& fname){
		file_input<> input(fname);
		
		SafeRootResult result;

		Root root;
		ScratchData scratch;
		parse<must<root_grammar>, run_action>(input, &root, &scratch);
		post_process(root);

		if (scratch.errors.size()) {
			std::vector<const char*>err_data;
			for (auto&e : scratch.errors){
				err_data.emplace_back(e.what());
			}
			result.result = reinterpret_cast<void*>(&err_data);
			result.is_error = true;
		} else {
			result.result = reinterpret_cast<void*>(&root);
			result.is_error = false;
		}
		return result;
	}
} // namespace broma
