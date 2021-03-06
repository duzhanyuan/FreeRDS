/**
 * main of session manager
 *
 * Copyright 2013 Thinstuff Technologies GmbH
 * Copyright 2013 DI (FH) Martin Haimberger <martin.haimberger@thinstuff.at>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "config.h"
#include <iostream>

#include <appcontext/ApplicationContext.h>

using namespace std;
int main(void)
{
	std::string test;
	APP_CONTEXT.startRPCEngine();
	APP_CONTEXT.loadModulesFromPath("/development/testModule/");
	cout << "Hello session manager" << endl;
	cin >>test;
	APP_CONTEXT.stopRPCEngine();
	return 0;
}
