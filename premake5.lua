ROOT_DIR = os.getcwd()

include ('vcpkg.lua')

workspace "RPFXplorer"
    configurations { "Debug", "Release" }
    platforms { "Win64" }
    language "C++"
    targetdir ( ROOT_DIR .. "/bin/%{cfg.buildcfg}" )

    cppdialect "C++20"

    files { "vcpkg.json" }

    group "dll/lib/rpf"
        include('Code/dll/lib/rpf')
    group ""

    group "dll/lib/rpf/tests"
        include('Code/tests/dll/rpf')
    group ""

    group "dll/shellext"
        include('Code/dll/shellext/rpfxplr')
    group ""

    group "exe/tools"
        include('Code/exe/tools/aulens')
        include('Code/exe/tools/modlense')
    group ""

if _ACTION == 'clean' then
    os.rmdir('bin')
    os.rmdir('obj')
    os.rmdir('.vs')
    os.remove('**.sln')
    os.remove('**.vcxproj')
    os.remove('**.vcxproj.*')
    os.remove('**.wixobj')
    os.remove('**.wixpdb')
    os.remove('**.msi')
end
