---@diagnostic disable: undefined-global, lowercase-global
workspace "EchoEngine"
    architecture "x64"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Echo/vendor/GLFW"