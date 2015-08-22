#pragma once

#include "rapidjson\document.h"
#include "rapidjson\writer.h"
#include "rapidjson\stringbuffer.h"
#include <iostream>

using namespace rapidjson;

namespace test{
	Document testJason(){
		const char * jason = "{\"project\":\"rapidjson\",\"stars\":10}";
		Document d;
		d.Parse(jason);
		return d;
	}
}