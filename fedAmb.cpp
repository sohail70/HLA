#include "fedAmb.h"

double fedAmb::convertTime(const LogicalTime& theTime)
{
	const HLAfloat64Time& castTime = dynamic_cast<const HLAfloat64Time&>(theTime);
	return castTime.getTime();
}

fedAmb::fedAmb()
{

	this->federateTime = 0.0;
	this->federateLookahead = 10;

	this->isRegulating = false;
	this->isConstrained = false;
	this->isAdvancing = false;
	this->isAnnounced = false;
	this->isReadyToRun = false;

}
fedAmb::~fedAmb()
{

}


void fedAmb::connectionLost(
	std::wstring const & faultDescription)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}


void fedAmb::reportFederationExecutions(
	FederationExecutionInformationVector const &
	theFederationExecutionInformationList)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}



void fedAmb::synchronizationPointRegistrationSucceeded(
	std::wstring const & label) // supplied C4)
	throw (
		FederateInternalError)
{
	wcout << L"Successfully registered sync point: "<< label << endl;
}

void fedAmb::synchronizationPointRegistrationFailed(
	std::wstring const & label,
	SynchronizationPointFailureReason reason)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}


void fedAmb::announceSynchronizationPoint(
	std::wstring  const & label,
	VariableLengthData const & theUserSuppliedTag)   // supplied C4
	throw (
		FederateInternalError)
{
	wcout << L"Synchronization point announced: " << label << endl;
	if (label.compare(L"ReadyToRun") == 0)
		this->isAnnounced = true;
}

void fedAmb::federationSynchronized(const std::wstring& label,
	const FederateHandleSet& failedSet)
	throw(FederateInternalError)
{
	wcout << L"Federation Synchronized: " << label << endl;
	if (label.compare(L"ReadyToRun") == 0)
		this->isReadyToRun = true;
}

void fedAmb::initiateFederateSave(
	std::wstring const & label) // supplied C4
	throw (
		UnableToPerformSave,
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}


void fedAmb::initiateFederateSave(
	std::wstring const & label,
	LogicalTime const & theTime) 
	throw(
		UnableToPerformSave,
		InvalidLogicalTime,
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}


void fedAmb::federationSaved()
throw (
	FederateInternalError)
{
	wcout << L"Not supported" << endl;
}


void fedAmb::federationNotSaved(
	SaveFailureReason theSaveFailureReason)
throw (
	FederateInternalError)
{
	wcout << L"Not supported" << endl;
}


void fedAmb::federationSaveStatusResponse(FederateHandleSaveStatusPairVector const & theFederateStatusVector) throw(FederateInternalError)
{
	wcout << L"Not supported" << endl;
}

void fedAmb::requestFederationRestoreSucceeded(
	std::wstring const & label) // supplied C4
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}


void fedAmb::requestFederationRestoreFailed(
	std::wstring const & label) // supplied C4
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}

void fedAmb::federationRestoreBegun()
throw (
	FederateInternalError)
{
	wcout << L"Not supported" << endl;
}


void fedAmb::initiateFederateRestore(
	std::wstring const & label,
	std::wstring const & federateName,
	FederateHandle handle)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}

void fedAmb::federationRestored()
throw (
	FederateInternalError)
{
	wcout << L"Not supported" << endl;
}


void fedAmb::federationNotRestored(
	RestoreFailureReason theRestoreFailureReason)
throw (
	FederateInternalError)
{
	wcout << L"Not supported" << endl;
}

void fedAmb::federationRestoreStatusResponse(
	FederateRestoreStatusVector const &
	theFederateRestoreStatusVector)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}
//////////////////////////////////////////////
void fedAmb::startRegistrationForObjectClass(
	ObjectClassHandle   theClass)      // supplied C1
	throw (
		ObjectClassNotPublished,
		FederateInternalError)
{
	if (theClass == country::GetCountryId())
	{
		country::SetRegistration(true);
		wcout << L"Turned registration on for Country class" << endl;
	}
	else
	{
		wcout << L"startRegistrationForObjectClass unknown class: " << endl;
	}
}


void fedAmb::stopRegistrationForObjectClass( 
	ObjectClassHandle   theClass)      // supplied C1
	throw (ObjectClassNotPublished,FederateInternalError)
{
	if (theClass == country::GetCountryId())
	{
		country::SetRegistration(false);
		wcout << L"Turned registration off for Country class" << endl;
	}
	else
	{
		wcout << L"stopRegistrationForObjectClass unknown class: " << endl;
	}
}





void fedAmb::turnInteractionsOn(
	InteractionClassHandle theHandle)
throw (
	InteractionClassNotPublished,
	FederateInternalError)
{
	country::setInteractionControl(true, theHandle);
}


void fedAmb::turnInteractionsOff(
	InteractionClassHandle theHandle)
throw (
	InteractionClassNotPublished,
	FederateInternalError)
{
	country::setInteractionControl(false, theHandle);
}


void fedAmb::objectInstanceNameReservationSucceeded(
	std::wstring const & theObjectInstanceName)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}

void fedAmb::objectInstanceNameReservationFailed(
	std::wstring const & theObjectInstanceName)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}

void fedAmb::multipleObjectInstanceNameReservationSucceeded(
	std::set<std::wstring> const & theObjectInstanceNames)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}

void fedAmb::multipleObjectInstanceNameReservationFailed(
	std::set<std::wstring> const & theObjectInstanceNames)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}

void fedAmb::discoverObjectInstance(
	ObjectInstanceHandle theObject,
	ObjectClassHandle theObjectClass,
	std::wstring const & theObjectInstanceName)
	throw (
		FederateInternalError)
{
	wcout << "Discovered object" << endl;
	if (theObjectClass == country::GetCountryId())
	{
		country* tmpPtr = new country(theObject); //to removeObjectInstance delete mishe!
	}
	else
	{
		wcout << L"Unknown Discovered object" << endl;
	}
}


void fedAmb::discoverObjectInstance(
	ObjectInstanceHandle theObject,
	ObjectClassHandle theObjectClass,
	std::wstring const & theObjectInstanceName,
	FederateHandle producingFederate)
	throw (
		FederateInternalError)
{
	wcout << "Discovered object" << endl;
	if (theObjectClass == country::GetCountryId())
	{
		country* tmpPtr = new country(theObject); 
	}
	else
	{
		wcout << L"Unknown Discovered object" << endl;
	}
}


void fedAmb::reflectAttributeValues(
	ObjectInstanceHandle theObject,
	AttributeHandleValueMap const & theAttributeValues,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	TransportationType theType,
	SupplementalReflectInfo theReflectInfo)
	throw (
		FederateInternalError) {
	country* pCountry = country::find(theObject);
	if (pCountry)
	{
		pCountry->update(theAttributeValues, theObject);
		pCountry->setLastTime(federateTime); 
	}
	else
	{
		wcout << "Object not known" << endl;
	}
}

void fedAmb::reflectAttributeValues(
	ObjectInstanceHandle theObject,
	AttributeHandleValueMap const & theAttributeValues,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	TransportationType theType,
	LogicalTime const & theTime,
	OrderType receivedOrder,
	SupplementalReflectInfo theReflectInfo)
	throw (
		FederateInternalError) 
{
	country* pCountry = country::find(theObject);
	if (pCountry)
	{
		pCountry->update(theAttributeValues, theObject);
		pCountry->setLastTime(federateTime);
	}
	else
	{
		wcout << "Object not known" << endl;
	}
}

void fedAmb::reflectAttributeValues(
	ObjectInstanceHandle theObject,
	AttributeHandleValueMap const & theAttributeValues,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	TransportationType theType,
	LogicalTime const & theTime,
	OrderType receivedOrder,
	MessageRetractionHandle theHandle,
	SupplementalReflectInfo theReflectInfo)
	throw (
		FederateInternalError)
{
	country* pCountry = country::find(theObject);
	if (pCountry)
	{
		pCountry->update(theAttributeValues, theObject);
		pCountry->setLastTime(federateTime);
	}
	else
	{
		wcout << "Object not known" << endl;
	}

}



void fedAmb::receiveInteraction(
	InteractionClassHandle theInteraction,
	ParameterHandleValueMap const & theParameterValues,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	TransportationType theType,
	SupplementalReceiveInfo theReceiveInfo)
	throw (
		FederateInternalError) {
	country::update(theInteraction,theParameterValues);
}


void fedAmb::receiveInteraction(
	InteractionClassHandle theInteraction,
	ParameterHandleValueMap const & theParameterValues,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	TransportationType theType,
	LogicalTime const & theTime,
	OrderType receivedOrder,
	SupplementalReceiveInfo theReceiveInfo)
	throw (
		FederateInternalError)
{

	country::update(theInteraction, theParameterValues);
}

void fedAmb::receiveInteraction(
	InteractionClassHandle theInteraction,
	ParameterHandleValueMap const & theParameterValues,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	TransportationType theType,
	LogicalTime const & theTime,
	OrderType receivedOrder,
	MessageRetractionHandle theHandle,
	SupplementalReceiveInfo theReceiveInfo)
	throw (
		FederateInternalError) 
{
	country::update(theInteraction, theParameterValues);
}


void fedAmb::removeObjectInstance(
	ObjectInstanceHandle theObject,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	SupplementalRemoveInfo theRemoveInfo)
	throw (
		FederateInternalError) 
{
	cout << "Removed object " << endl;
	country* pCountry = country::find(theObject);
	if (pCountry)
	{
		delete pCountry;
	}
}


void fedAmb::removeObjectInstance(
	ObjectInstanceHandle theObject,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	LogicalTime const & theTime,
	OrderType receivedOrder,
	MessageRetractionHandle theHandle,
	SupplementalRemoveInfo theRemoveInfo)
	throw (
		FederateInternalError)
{
	cout << "Removed object " << endl;
	country* pCountry = country::find(theObject);
	if (pCountry)
	{
		delete pCountry;
	}
}

void fedAmb::removeObjectInstance(
	ObjectInstanceHandle theObject,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	LogicalTime const & theTime,
	OrderType receivedOrder,
	SupplementalRemoveInfo theRemoveInfo)
	throw (
		FederateInternalError)
{
	cout << "Removed object " << endl;
	country* pCountry = country::find(theObject);
	if (pCountry)
	{
		delete pCountry;
	}
}


void fedAmb::attributesInScope(
	ObjectInstanceHandle theObject,
	AttributeHandleSet const & theAttributes)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}

void fedAmb::attributesOutOfScope(
	ObjectInstanceHandle theObject,
	AttributeHandleSet const & theAttributes)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}

void fedAmb::provideAttributeValueUpdate(
	ObjectInstanceHandle theObject,
	AttributeHandleSet const & theAttributes,
	VariableLengthData const & theUserSuppliedTag)
	throw (
		ObjectInstanceNotKnown,
		AttributeNotRecognized,
		AttributeNotOwned,
		FederateInternalError)
{
	country *pCountry = country::find(theObject);

	if (pCountry)
	{
		AttributeHandle attrHandle;
		AttributeHandleSet::iterator i;
		for (i = theAttributes.begin(); i != theAttributes.end(); i++)
		{
			attrHandle = *i;
			if (attrHandle == country::GetPopulationId())
			{
				pCountry->setPop(pCountry->getPopulation());
			}
			else if (attrHandle == country::GetNameId())
			{
				pCountry->setName(pCountry->getName());
			}
		}
	}
}




void fedAmb::turnUpdatesOnForObjectInstance(
	ObjectInstanceHandle        theObject,     // supplied C1
	const AttributeHandleSet& theAttributes) // supplied C4
	throw (ObjectInstanceNotKnown,
		AttributeNotRecognized,
		AttributeNotOwned,
		FederateInternalError)
{
	country* pCountry = country::find(theObject);

	if (pCountry)
	{
		pCountry->setUpdateControl(true, theAttributes);
	}
	else
	{
		cout << " Country object not found" << endl;
	}
}

void fedAmb::turnUpdatesOnForObjectInstance(
	ObjectInstanceHandle theObject,
	AttributeHandleSet const & theAttributes,
	std::wstring const & updateRateDesignator)
	throw (
		FederateInternalError)
{
	country* pCountry = country::find(theObject);

	if (pCountry)
	{
		pCountry->setUpdateControl(true, theAttributes);
	}
	else
	{
		cout << "Country object not found" << endl;
	}
}


void fedAmb::turnUpdatesOffForObjectInstance(
	ObjectInstanceHandle        theObject,      // supplied C1
	const AttributeHandleSet& theAttributes) // supplied C4
	throw (ObjectInstanceNotKnown,
		AttributeNotRecognized,
		AttributeNotOwned,
		FederateInternalError)
{
	country* pCountry = country::find(theObject);

	if (pCountry)
	{
		pCountry->setUpdateControl(false, theAttributes);
	}
	else
	{
		cout << "Country object not found" << endl;
	}
}

void fedAmb::confirmAttributeTransportationTypeChange(
	ObjectInstanceHandle theObject,
	AttributeHandleSet theAttributes,
	TransportationType theTransportation)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}

void fedAmb::reportAttributeTransportationType(
	ObjectInstanceHandle theObject,
	AttributeHandle theAttribute,
	TransportationType theTransportation)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}

void fedAmb::confirmInteractionTransportationTypeChange(
	InteractionClassHandle theInteraction,
	TransportationType theTransportation)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}
void fedAmb::reportInteractionTransportationType(
	FederateHandle federateHandle,
	InteractionClassHandle theInteraction,
	TransportationType  theTransportation)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}


void fedAmb::requestAttributeOwnershipAssumption(
	ObjectInstanceHandle theObject,
	AttributeHandleSet const & offeredAttributes,
	VariableLengthData const & theUserSuppliedTag)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}


void fedAmb::requestDivestitureConfirmation(
	ObjectInstanceHandle theObject,
	AttributeHandleSet const & releasedAttributes)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}


void fedAmb::attributeOwnershipAcquisitionNotification(
	ObjectInstanceHandle theObject,
	AttributeHandleSet const & securedAttributes,
	VariableLengthData const & theUserSuppliedTag)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}


void fedAmb::attributeOwnershipUnavailable(
	ObjectInstanceHandle theObject,
	AttributeHandleSet const & theAttributes)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}


void fedAmb::requestAttributeOwnershipRelease(
	ObjectInstanceHandle theObject,
	AttributeHandleSet const & candidateAttributes,
	VariableLengthData const & theUserSuppliedTag)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}


void fedAmb::confirmAttributeOwnershipAcquisitionCancellation(
	ObjectInstanceHandle theObject,
	AttributeHandleSet const & theAttributes)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}


void fedAmb::informAttributeOwnership(
	ObjectInstanceHandle theObject,
	AttributeHandle theAttribute,
	FederateHandle theOwner)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}

void fedAmb::attributeIsNotOwned(
	ObjectInstanceHandle theObject,
	AttributeHandle theAttribute)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}

void fedAmb::attributeIsOwnedByRTI(
	ObjectInstanceHandle theObject,
	AttributeHandle theAttribute)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}





void fedAmb::timeRegulationEnabled(
	const  LogicalTime& theFederateTime) // supplied C4
	throw (InvalidLogicalTime,
		NoRequestToEnableTimeRegulationWasPending,
		FederateInternalError)
{
	
	this->isRegulating = true;
	this->federateTime = convertTime(theFederateTime);
	wcout << L"Time granted (timeRegulationEnabled) to: "
		<< federateTime << endl;
}

void fedAmb::timeConstrainedEnabled(
	const LogicalTime& theFederateTime) // supplied C4
	throw (InvalidLogicalTime,
		NoRequestToEnableTimeConstrainedWasPending,
		FederateInternalError)
{
	
	this->isConstrained = true;
	this->federateTime = convertTime(theFederateTime);
	wcout << L"Time granted (timeConstrainedEnabled) to: "
		<< federateTime << endl;
}

void fedAmb::timeAdvanceGrant(
	const LogicalTime& theFederateTime) // supplied C4
	throw (InvalidLogicalTime,
		JoinedFederateIsNotInTimeAdvancingState,
		FederateInternalError)
{
	
	this->isAdvancing = true;
	this->federateTime = convertTime(theFederateTime);
	wcout << L"Time granted (timeAdvanceGrant) to: "
		<< federateTime << endl;
}

void fedAmb::requestRetraction(
	MessageRetractionHandle theHandle)
	throw (
		FederateInternalError)
{
	wcout << L"Not supported" << endl;
}


