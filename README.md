# Github Unfollowers Checker
GithubUnfollowersChecker - find GitHub users you follow who don't follow you back.

## Dependencies
* [cpr](https://github.com/libcpr/cpr)
* [nlohmann-json](https://github.com/nlohmann/json)

## Build local Windows/Linux
```shell
vcpkg install cpr nlohmann-json
vcpkg integrate install

cd GithubUnfollowersChecker
mkdir build && cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE="path/to/vcpkg/scripts/buildsystems/vcpkg.cmake"

cmake --build . --config Release
```

## Usage
```shell
GithubUnfollowersChecker.exe <github-username>
```
