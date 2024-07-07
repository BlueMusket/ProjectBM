// Fill out your copyright notice in the Description page of Project Settings.


#include "SharedPacket.h"
#include "Shared_generated.h"


uint8_t* CG_Login::Pack()
{
	flatbuffers::FlatBufferBuilder builder;
	builder.Finish(CreateFCG_LoginDirect(builder, "helloWorld", "worldHelloPwd"));

	return builder.GetBufferPointer();

	return nullptr;
}

void CG_Login::UnPack(uint8_t* buffer)
{
	auto packet = flatbuffers::GetRoot<FCG_Login>(buffer);

	std::string name = packet->name()->c_str();
	std::string pwd = packet->pwd()->c_str();
}