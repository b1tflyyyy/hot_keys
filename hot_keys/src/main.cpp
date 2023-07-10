#include "../parser/parser.hpp"

// TODO: create models single button && pair of button ?

int main()
{  
    Parser parser;
    parser.m_parse_all_data();
    parser.m_set_to_map();

    try
    {
        for (const auto& [button_value, path] : parser.get_single_buttons())
        {
            std::wcout << button_value << " " << path << '\n';
        }
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << '\n';
    }

    return 0;
}
