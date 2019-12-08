#include "federate.h"
#include "fedAmb.h"
#include <RTI\RTI1516.h>
#include <RTI\time\HLAfloat64Interval.h>
#include <RTI\time\HLAfloat64Time.h>
#include <RTI\Exception.h>
#include <Windows.h>

//static var init
RTIambassador* country::rtiamb;
fedAmb* country::fedamb;
country*   country::countryExtent[10] = {nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr 
,nullptr ,nullptr }; 
unsigned int country::extentCardinality = 0;
bool country::doRegistry = true;
bool country::sendCommInteraction = true;

ObjectClassHandle country::countryTypeId = {};
AttributeHandle country::nameTypeId = {};
AttributeHandle country::popTypeId = {};
InteractionClassHandle country::commTypeId = {};
ParameterHandle  country::commMsgTypeId = {};


country::country()
{
	countryExtent[extentCardinality++] = this;
	
	this->defaultPop = 100;
	this->growthRate = 0.001;
	this->lastTime = 0.0;

	setName({});
	setPop(defaultPop);
	
}

country::country(wstring name, wstring popStr)
{
	countryExtent[extentCardinality++] = this;
	this->growthRate = 0.001;
	this->defaultPop = 100;
	this->lastTime = 0.0;

	setPop(stod(popStr));
	setName(name);
}

country::country(wstring name, double pop)
{
	this->growthRate = 0.001;
	this->defaultPop = 100;
	this->lastTime = 0.0;

	setPop(pop);
	setName(name);
}

country::country(ObjectInstanceHandle id)
{
	countryExtent[extentCardinality++] = this;
	this->instanceId = id;
	this->growthRate = 0.001;
	this->defaultPop = 100;
	this->lastTime = 0.0;

	setName({});
	setPop(defaultPop);
}


country::~country()
{
	country* pCountry = nullptr;
	unsigned int i = 0;
	for ( i = 0; i < country::extentCardinality; i++)
	{
		pCountry = country::countryExtent[i];
		if (pCountry &&pCountry->getInstanceId() == this->getInstanceId())
		{
			break;
		}
	}
	if (pCountry)
	{
		for (unsigned int j = i; (j < country::extentCardinality)
			&& (country::countryExtent[i] != nullptr); j++)
		{
			country::countryExtent[j] = country::countryExtent[j + 1];
		}
		country::extentCardinality -= 1; 

		if ((rtiamb != nullptr) && i == 0)
		{
			auto_ptr<HLAfloat64Time> Time(new HLAfloat64Time(getLastTime() + fedamb->federateLookahead));
			VariableLengthData tag((void*)"Finito!", 40);
			
			(void)rtiamb->deleteObjectInstance(this->getInstanceId(), tag, *Time);
		}
		else
		{

		}
	}

	if (!name.empty())
	{
		name = {};
	}
}

void country::setName(wstring name)
{
	this->name = name;
}

void country::setPop( double pop)
{
	this->pop = pop;
}

void country::setLastTime(double time)
{
	this->lastTime = time;
}

void country::initializeHandles()
{
	this->countryTypeId = country::rtiamb->getObjectClassHandle(L"HLAobjectRoot.Country");
	this->nameTypeId = country::rtiamb->getAttributeHandle(countryTypeId, L"Name");
	this->popTypeId = country::rtiamb->getAttributeHandle(countryTypeId, L"Population");
	this->commTypeId = country::rtiamb->getInteractionClassHandle(L"HLAinteractionRoot.Communication");
	this->commMsgTypeId = country::rtiamb->getParameterHandle(commTypeId,L"Sohail");
	//this->commMsgTypeId = country::rtiamb->getParameterHandle(commTypeId, L"Message");
}

void country::PublishAndSubscribe()
{
	AttributeHandleSet* countryAtts = new AttributeHandleSet();
	countryAtts->insert(this->nameTypeId);
	countryAtts->insert(this->popTypeId);
	country::rtiamb->subscribeObjectClassAttributes(countryTypeId, *countryAtts);
	country::rtiamb->publishObjectClassAttributes(countryTypeId, *countryAtts);
	delete countryAtts;
	country::rtiamb->subscribeInteractionClass(commTypeId);
	country::rtiamb->publishInteractionClass(commTypeId);
}
void country::enableTimeRegulationAndConstrained()
{
	///////////////////////////////////////
	try
	{


		country::rtiamb->enableTimeConstrained();
		
		while (country::fedamb->isConstrained == false)
			country::rtiamb->evokeMultipleCallbacks(0.1, 1.0);
	}
	catch (Exception &e)
	{
		wcout << e.what() << endl;
	}
	///////////////////////////////////////
	try
	{
	double fedLookahead = country::fedamb->federateLookahead;
	auto_ptr<HLAfloat64Interval> inter(new HLAfloat64Interval(fedLookahead));
	country::rtiamb->enableTimeRegulation(*inter);

	
	while (country::fedamb->isRegulating == false)
		country::rtiamb->evokeMultipleCallbacks(0.1, 1);
	}
	catch (Exception &e)
	{
		wcout << e.what() << endl;
	}

}
void country::registerObject()
{
	if(country::rtiamb!=nullptr)
		instanceId = country::rtiamb->registerObjectInstance(country::GetCountryId());
}

void country::update(double newTime)
{
	double delta = newTime - this->getLastTime();
	this->setLastTime(newTime);
	if (delta > 0.0)
	{
		setPop(pop + pop * growthRate*delta);
	}
	updateAtt();
}

void country::updateAtt()
{
	AttributeHandleValueMap* pCountryAttributes= new AttributeHandleValueMap();
	if (country::rtiamb != nullptr)
	{
		try
		{
			AttributeHandle attId = this->GetNameId();;
			VariableLengthData attValue; attValue.setData(& ws2s(this->getName()), 100); //(name.size() + 1)*sizeof(char)
			pCountryAttributes->insert({ attId,attValue });

			AttributeHandle attId1 = this->GetPopulationId();
			VariableLengthData attValue1; attValue1.setData(& (to_string(this->getPopulation())), 100);
			pCountryAttributes->insert({ attId1, attValue1 });
			VariableLengthData tag((void*)"Hi!", 4);
			auto_ptr<HLAfloat64Time> Time(new HLAfloat64Time(country::fedamb->federateTime + fedamb->federateLookahead));
			country::rtiamb->updateAttributeValues(this->getInstanceId(), *pCountryAttributes, tag,*Time);
			
			pCountryAttributes->empty();
			delete pCountryAttributes;
		}
		catch (Exception &e)
		{
			wcout << L"Update error: " << e.what() << endl;
		}
		////////////////////////////////////////////////////////////////////////
	
		static int periodicMessage = 0;
		if ((periodicMessage++ % 10) == 0)
		{
			ParameterHandleValueMap pParams;
			string pMsg = "HEY BOY!";
			VariableLengthData value(&pMsg, 100);
			pParams.insert(make_pair(this->GetMessageId(), value));
			try
			{
				country::rtiamb->sendInteraction(commTypeId,pParams,value);
			}
			catch (Exception& e)
			{
				wcout << "Error in sendInteraction" << e.what() << endl;
			}
		}	
	}
}

void country::timeAdvance(double timeStep)
{
	country::fedamb->isAdvancing = false;
	auto_ptr<HLAfloat64Time> newTime(new HLAfloat64Time(country::fedamb->federateTime + timeStep));
	try
	{
		country::rtiamb->timeAdvanceRequest(*newTime);
	}
	catch (Exception &e)
	{
		wcout << e.what() << endl;
	}

	while (country::fedamb->isAdvancing ==false)
	{
		country::rtiamb->evokeMultipleCallbacks(0.1, 1.0);
	}

}

void country::runFederate(shared_ptr<country> countryPtr)
{
	RTIambassadorFactory factory = RTIambassadorFactory();
	country::rtiamb = factory.createRTIambassador().release();
	
	/////////////////////////
	//  connect to the RTI //
	/////////////////////////
	country::fedamb = new fedAmb();
	
	try
	{
		country::rtiamb->connect(*country::fedamb, HLA_EVOKED);
	}
	catch (Exception& e)
	{
		wcout << L"Connection failed: " << e.what() << endl;
	}

	//////////////////////////////
	//  create  the federation  //
	//////////////////////////////
	try
	{
		wcout << L"Creating Federation..." << endl;
		wstring fom = L"I:/work/HLA evolved/HLA_Evolved/fd.xml";
		country::rtiamb->createFederationExecution(L"World", fom);
		wcout << L"done" << endl;
	}
	catch (Exception &e)
	{
		wcout << L"Creating Federation Failed: " << e.what() << endl;
	}
	
	//////////////////////////
	// join the federation	//
	//////////////////////////
	FederateHandle federateId = country::rtiamb->joinFederationExecution(countryPtr->name, L"World");
	wcout << L"Joined Federation as " << countryPtr->name<<" with id: "<<federateId<< endl;


	initializeHandles();
	PublishAndSubscribe();
	registerObject();
	enableTimeRegulationAndConstrained();
	
	try
	{
		cout << "enabling asynchronous delivery" << endl;

		country::rtiamb->enableAsynchronousDelivery();
	}
	catch (Exception& e)
	{
		cout << "error:" << &e << endl;
	}

	try
	{
		country::rtiamb->enableAttributeRelevanceAdvisorySwitch();
	}
	catch (Exception& e)
	{
		cerr << "error:" << &e << endl;
	}


	int counter = 0;
	while (counter++ < 1000)
	{
		update(country::fedamb->federateTime);
		country* pCountry = nullptr;
		for (unsigned int i = 0; i < extentCardinality; i++)
		{
			pCountry = countryExtent[i];
			if (pCountry)
				wcout << "Country[" << i << "]" <<" Name: " <<pCountry->getName()<<
				" Population: " << pCountry->getPopulation()<< " Time: " << country::fedamb->federateTime<<endl;
		}

		timeAdvance(10.0);

	}
	try
	{
		rtiamb->resignFederationExecution(DELETE_OBJECTS);
		cout << "Resigning federation" << endl;
	}
	catch (Exception &e)
	{
		wcout <<L"error resigning"<< e.what() << endl;
	}

	try
	{
		rtiamb->destroyFederationExecution(L"World");
	}
	catch (Exception &e)
	{
		wcout << L"I'm not the last federation for destruction" << e.what() << endl;
	}

}


void country::update(const  AttributeHandleValueMap&  theAttributes, ObjectInstanceHandle objectHandle)
{
	AttributeHandle attrHandle;
	AttributeHandleValueMap::const_iterator it;

	for (it = theAttributes.begin(); it != theAttributes.end(); it++)
	{
		attrHandle = (*it).first;
		auto var = (*it).second.size();
		if (attrHandle == country::GetPopulationId())
		{
			double population;
			VariableLengthData variable = it->second;
			const void* temp = variable.data();
			string popString;
			popString = *((string*)temp);
			population = stod(popString);
			setPop((double)population);
		}
		else if (attrHandle == country::GetNameId())
		{
			VariableLengthData variable = it->second;
			const void* temp = variable.data();
			string* nameString;
			nameString = (string*)temp;	
			setName(s2ws(*nameString));
		}
	}



}


void country::update(InteractionClassHandle theInteraction, const ParameterHandleValueMap& theParameters)
{
	if (theInteraction == country::GetCommId())
	{
		ParameterHandle paramHandle;
		unsigned long          valueLength;
		ParameterHandleValueMap::const_iterator i;
		for (i = theParameters.begin(); i != theParameters.end(); i++)
		{
			ParameterHandle const & paramHandle = i->first;
			VariableLengthData value = i->second;
			valueLength = value.size();
			if (paramHandle == country::GetMessageId())
			{
				VariableLengthData value =  i->second;
				auto str = value.data();
				auto val = *((string*)str);
				cout << "Interaction Received: " << val << endl;
			}
			else
			{
				cout << "Don't know about this parameter"<< endl;
			}
		}
	}
	else
	{
		wcout << L"Recieved an interaction class I don't know about" << endl;
	}
}

void country::setInteractionControl(bool status, InteractionClassHandle theClass)
{
	if (theClass == commTypeId)
	{
		country::sendCommInteraction = status;
		wstring str = country::sendCommInteraction ? L"ON" : L"OFF";
		wcout << "Turning communication interaction " << str << endl;
	}
	else
	{
		wcout << L"Unknown interaction" << endl;
	}
}

void country::SetRegistration(bool status)
{
	country::doRegistry = status;
}


country* country::find(ObjectInstanceHandle objectId)
{
	country* pCountry = nullptr;
	for (unsigned int i = 0; i < extentCardinality ; i++)
	{
		pCountry = countryExtent[i];
		if (pCountry && (pCountry->instanceId == objectId))
			break;
	}
	return pCountry;
}



void country::setUpdateControl(bool status,
	const AttributeHandleSet& theAttrHandles)
{
	AttributeHandle attrHandle;
	for (unsigned int i = 0; i < theAttrHandles.size(); i++)
	{
		AttributeHandleSet::iterator it = theAttrHandles.begin();
		advance(it, i);
		attrHandle = *it;

		if (attrHandle == country::GetPopulationId())
		{
			sendPopulationAttrUpdates = status;

			const char *pStr = sendPopulationAttrUpdates ? "ON" : "OFF";

			cout << "Turning Country.Population Updates "
				<< pStr << " for object "
				<< " ." << endl;
		}
		else if (attrHandle == country::GetNameId())
		{
			sendNameAttrUpdates = status;
			const char *pStr = sendNameAttrUpdates ? "ON" : "OFF";

			cout << "Turning Country.Name Updates "
				<< pStr << " for object " 
				<< " ." << endl;
		}
	}
}

std::wstring s2ws(const std::string& str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}
std::string ws2s(const std::wstring& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
	char* buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, buf, len, 0, 0);
	std::string r(buf);
	delete[] buf;
	return r;
}
