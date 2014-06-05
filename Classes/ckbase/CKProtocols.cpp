#include "CKProtocols.h"
//
// generic getters for properties
//
const Value& PropertyProtocol::getValue(const std::string& key, const Value& defaultValue) const
{
	auto iter = _valueDict.find(key);
	if (iter != _valueDict.cend())
		return _valueDict.at(key);
	return defaultValue;
}

void PropertyProtocol::setValue(const std::string& key, const Value& value)
{
	_valueDict[key] = value;
}

std::string PropertyProtocol::getInfo() const
{
	// Dump
	Value forDump = Value(_valueDict);
	return forDump.getDescription();
}