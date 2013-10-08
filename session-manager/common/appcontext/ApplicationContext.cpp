/**
 * Application Context of Session Manager
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

#include "ApplicationContext.h"

namespace freerds{
	namespace sessionmanager{


	ApplicationContext::ApplicationContext(){

		wLogLayout* layout;
		wLogAppender* appender;

		WLog_Init();

		mWLogRoot = WLog_GetRoot();

		WLog_SetLogAppenderType(mWLogRoot, WLOG_APPENDER_CONSOLE);

		appender = WLog_GetLogAppender(mWLogRoot);
		WLog_ConsoleAppender_SetOutputStream(mWLogRoot, (wLogConsoleAppender*) appender, WLOG_CONSOLE_STDERR);

		layout = WLog_GetLogLayout(mWLogRoot);
		WLog_Layout_SetPrefixFormat(mWLogRoot, layout, "[%lv:%mn] [%fl|%fn|%ln] - ");

		WLog_OpenAppender(mWLogRoot);


	}


	ApplicationContext::~ApplicationContext(){

		WLog_CloseAppender(mWLogRoot);

		WLog_Uninit();


	}

	sessionNS::SessionStore * ApplicationContext::getSessionStore(){
		return &mSessionStore;
	}

	int ApplicationContext::startRPCEngine(){
		return mRpcEngine.startEngine();
	}

	int ApplicationContext::stopRPCEngine(){
		return mRpcEngine.stopEngine();
	}

	SignalingQueue<callNS::Call> * ApplicationContext::getRpcOutgoingQueue(){
		return &mRpcOutgoingCalls;
	}



    }
}
