#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <regex>
#include <optional>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::optional<std::string> ExtractNextPageUrl(const std::string& linkHeader)
{
    const std::regex next_page_regex{ R"(<([^>]+)>;\s*rel="next")" };
    const std::sregex_iterator it{ linkHeader.begin(), linkHeader.end(), next_page_regex };

	if (it != std::sregex_iterator()) 
    {
        return (*it)[1].str();
    }

    return std::nullopt;
}

std::unordered_set<std::string> FetchAllUsers(const std::string& username, const std::string& endpoint)
{
    std::unordered_set<std::string> users;
    std::string url{ "https://api.github.com/users/" + username + "/" + endpoint };

    while (!url.empty()) 
    {
        cpr::Response response{ cpr::Get(
            cpr::Url{ url },
            cpr::Header{ {"User-Agent", "cpp-github-unfollowers-checker"} }
        ) };

        if (response.status_code != 200) 
        {
            throw std::runtime_error("Request failed: " + response.status_line);
        }

        const auto parsed_json{ json::parse(response.text) };
        for (const auto& user : parsed_json) 
        {
            users.insert(user["login"].get<std::string>());
        }

        url = ExtractNextPageUrl(response.header["Link"]).value_or("");
    }

    return users;
}

int main(int argc, char* argv[]) noexcept
{
    try 
    {
        if (argc != 2) 
        {
            std::cerr << "Usage: " << argv[0] << " <github-username>\n";
            return 1;
        }

        const std::string username{ argv[1] };
        const auto following{ FetchAllUsers(username, "following") };
        const auto followers{ FetchAllUsers(username, "followers") };

        std::vector<std::string> non_followers;
        for (const auto& user : following) 
        {
            if (!followers.contains(user)) 
            {
                non_followers.push_back(user);
            }
        }

        std::cout << "Users not following back:\n";
        for (const auto& user : non_followers) 
        {
            std::cout << "https://github.com/" << user << "\n";
        }
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
