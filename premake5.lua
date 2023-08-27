workspace "GLFWTest"
	architecture "x86_64"

configurations
{
	"Debug",
	"Release",
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "GLFWTest"