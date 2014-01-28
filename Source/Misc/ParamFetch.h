#pragma once

namespace Misc {
	class ParamFetch {
	public:
		template <typename T, typename Q> static T Fetch(std::map<std::string, std::string> target_map, std::string key) {
			std::string string_rep;
			std::stringstream conv_ss;
			T output_value;

			std::string type_name = typeid(Q).name();

			try {
				string_rep = target_map.at(key);
			}
			catch (std::out_of_range) {
				Neptune::Logging::GeneralLogger::Handle()->Log(Logging::LOG_APP | Logging::LOG_USER,"[GLPTParamFetch] Tried to index undeclared parameter \"" + key + "\"! (called by " + type_name + ")");

				return NULL;
			}

			conv_ss << string_rep;

			conv_ss >> output_value;

			return output_value;
		}
	};
}