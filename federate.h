#pragma once
#include <iostream>
#include "RTI\RTI1516.h"
#include<Windows.h>
class fedAmb;

using namespace std;
using namespace rti1516e;

std::wstring s2ws(const std::string& str);
std::string ws2s(const std::wstring& s);
class country 
{
	private:
		static RTIambassador* rtiamb;
		static fedAmb* fedamb;

		static ObjectClassHandle countryTypeId;
		static AttributeHandle nameTypeId;
		static AttributeHandle popTypeId;
		static InteractionClassHandle commTypeId;
		static ParameterHandle  commMsgTypeId;

		ObjectInstanceHandle instanceId;
		
		wstring name;
		double pop;
		
		static bool doRegistry;
		static bool sendCommInteraction;
		
		double growthRate;
		double defaultPop;
		double lastTime;

		bool sendNameAttrUpdates;
		bool sendPopulationAttrUpdates;


	public:
		static country*      countryExtent[10];
		static unsigned int  extentCardinality;
		void setLastTime(double time);
		void setName(wstring name);
		void setPop(double pop);

		country();
		country(wstring name, wstring popStr);
		country(wstring name, double pop);

		country(ObjectInstanceHandle id); //when new object is discovered
		virtual ~country();


		
		void initializeHandles(); 
		void PublishAndSubscribe();
		void enableTimeRegulationAndConstrained();
		void registerObject();
		void update(double newTime);
		void updateAtt();
		void timeAdvance(double timeStep);
		void runFederate(shared_ptr<country> countryPtr);

		void update(const  AttributeHandleValueMap&  theAttributes, ObjectInstanceHandle objectHandle);
		static void update(InteractionClassHandle theInteraction, const ParameterHandleValueMap& theParameters);


		static void setInteractionControl(bool status, InteractionClassHandle theClass);
		static void SetRegistration(bool status);

		static country* find(ObjectInstanceHandle objectId);

		void setUpdateControl(bool status,
			const AttributeHandleSet& theAttrHandles);


		double getLastTime()
		{
			return lastTime;
		};

		double GetLastTimePlusLookahead()
		{
			return lastTime
				+ 1.0;
		};

		
		wstring getName()
		{
			return name;
		};
		double getPopulation()
		{
			return pop;
		};
		ObjectInstanceHandle getInstanceId()
		{
			return instanceId;
		};



		static ObjectClassHandle GetCountryId() 
		{
			return countryTypeId;
		};
		static AttributeHandle GetNameId()
		{
			return nameTypeId;
		};
		static AttributeHandle GetPopulationId() 
		{
			return popTypeId;
		};
		static InteractionClassHandle GetCommId()
		{
			return commTypeId;
		};
		static ParameterHandle GetMessageId()
		{
			return commMsgTypeId;
		};
		
		

};
