// Fill out your copyright notice in the Description page of Project Settings.


#include "FlatHandler.h"
#include "Trade_generated.h"

CFlatHandler::CFlatHandler()
{
	m_Num = 5;
}

CFlatHandler::~CFlatHandler()
{
}


uint8_t* CFlatHandler::Pack()
{
	flatbuffers::FlatBufferBuilder builder;
	builder.Finish(CreateFCT_LoginDirect(builder, "helloWorld", "worldHelloPwd"));

	return builder.GetBufferPointer();

	return nullptr;
}

void CFlatHandler::UnPack(uint8_t* buffer)
{
	auto packet = flatbuffers::GetRoot<FCT_Login>(buffer);

	std::string name = packet->name()->c_str();
	std::string pwd = packet->pwd()->c_str();
}