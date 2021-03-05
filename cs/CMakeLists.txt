cmake_minimum_required(VERSION 3.12)

project(MyWinFormApp LANGUAGES CSharp)
 
add_executable(hash-trash hash-trash.cs)

set_property(TARGET hash-trash PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.6")
set(CMAKE_CSharp_FLAGS "/langversion:latest")

set_property(TARGET hash-trash PROPERTY VS_DOTNET_REFERENCES
    "Microsoft.CSharp"
    "System"
    "System.Core"
    "System.Data"
)
