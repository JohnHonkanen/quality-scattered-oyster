#include "Material.h"


Material::Material(string name, Shader program):Component(name)
{
	Material::program = program;
}

Material::~Material()
{
}
