#include "StageLight.h"
#include <vector>
#include <algorithm>


std::vector<GTAObject> sceneDirectorLightObject = {
	getGTAObjectFromObjName("prop_sd_spot_01"),
	getGTAObjectFromObjName("prop_sd_spot_02"),
	getGTAObjectFromObjName("prop_sd_spot_03"),
	getGTAObjectFromObjName("prop_sd_spot_04"),
	getGTAObjectFromObjName("prop_sd_spot_05"),
	getGTAObjectFromObjName("prop_sd_spot_06"),
	getGTAObjectFromObjName("prop_sd_spot_07"),
	getGTAObjectFromObjName("prop_sd_spot_08"),
	getGTAObjectFromObjName("prop_sd_spot_09"),
	getGTAObjectFromObjName("prop_sd_spot_10"),
	getGTAObjectFromObjName("prop_sd_spot_11"),
	getGTAObjectFromObjName("prop_sd_spot_12"),
	getGTAObjectFromObjName("prop_sd_spot_13"),
	getGTAObjectFromObjName("prop_sd_spot_14"),
	getGTAObjectFromObjName("prop_sd_spot_15"),
};

std::vector<GTAObject> getSceneDirectorLightObject() {
	return sceneDirectorLightObject;
}

GTAObject getDefaultSceneDirectorLightObject() {
	return getGTAObjectFromObjName("prop_sd_spot_01");
}

GTAObject getNextSceneDirectorLightObject(GTAObject lightObject) {

	//int foundIndex = find(spotLightColors.begin(), spotLightColors.end(), lightObject) - spotLightColors.begin();
	//see http://stackoverflow.com/questions/14225932/search-for-a-struct-item-in-a-vector-by-member-data
	int foundIndex = std::find_if(sceneDirectorLightObject.begin(), sceneDirectorLightObject.end(), [=](GTAObject const& aLightObject) {
		return (aLightObject.title.compare(lightObject.title) ==0) ;
	}) - sceneDirectorLightObject.begin();
	if (foundIndex + 1 >= sceneDirectorLightObject.size()) {//aLightObject not found or in last element
		return sceneDirectorLightObject[0];
	}
	else {
		return sceneDirectorLightObject[foundIndex + 1];
	}
}


void StageLight::moveLight(Vector3 lightPosition, Vector3 lightRotation)
{
	m_lightPosition = lightPosition;
	m_lightRotation = lightRotation;
	//update current position (rotation ignored for now)
	if (m_lightObject.objReference != 0) {
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(m_lightObject.objReference, m_lightPosition.x, m_lightPosition.y, m_lightPosition.z, 0, 0, 1);
	}
}

void StageLight::swapLightObject(GTAObject newLightObject)
{
	//update current position and rotation
	if (m_lightObject.objReference == 0) {
		Vector3 currentPosition = ENTITY::GET_ENTITY_COORDS(m_lightObject.objReference, true);
		m_lightPosition = currentPosition;
	}
	//delete old object
	if (m_lightObject.objReference != 0) {
		OBJECT::DELETE_OBJECT(&m_lightObject.objReference);
	}
	m_lightObject = newLightObject;

	//create object
	if (m_lightObject.objHash == -1) {
		m_lightObject.objHash = GAMEPLAY::GET_HASH_KEY(m_lightObject.objName);
	}

	STREAMING::REQUEST_MODEL(m_lightObject.objHash);
	DWORD ticksStart = GetTickCount();
	while (!STREAMING::HAS_MODEL_LOADED(m_lightObject.objHash))
	{
		WAIT(0);
		if (GetTickCount() - ticksStart > 5000) {
			log_to_file("Failed to load GTAObject name:" + std::string(m_lightObject.objName) + " Hash:" + std::to_string(m_lightObject.objHash));
			set_status_text("Failed to load objects");
			return;
		}
	}

	int newObjectRef = OBJECT::CREATE_OBJECT(m_lightObject.objHash, m_lightPosition.x, m_lightPosition.y, m_lightPosition.z, true, true, false);
	ENTITY::SET_ENTITY_ROTATION(newObjectRef, m_lightRotation.x + 180, 0, m_lightRotation.z, 2, true);
	m_lightObject.objReference = newObjectRef;
}

void StageLight::setHasFlicker(std::vector<StageLightFlicker> flickerEvents)
{
	m_hasFlicker = true;
	m_flickerEvents = flickerEvents;
}

void StageLight::stopFlicker()
{
	m_hasFlicker = false;
}

StageLight::StageLight(Vector3 lightPosition, Vector3 lightRotation, GTAObject lightObject)
{
	m_lightPosition = lightPosition;
	m_lightRotation = lightRotation; 
	m_lightObject = lightObject;
	
	//create object
	if (m_lightObject.objReference == 0) {
		if (m_lightObject.objHash == -1) {
			m_lightObject.objHash = GAMEPLAY::GET_HASH_KEY(m_lightObject.objName);
		}

		STREAMING::REQUEST_MODEL(m_lightObject.objHash);
		DWORD ticksStart = GetTickCount();
		while (!STREAMING::HAS_MODEL_LOADED(m_lightObject.objHash))
		{
			WAIT(0);
			if (GetTickCount() - ticksStart > 5000) {
				log_to_file("Failed to load GTAObject name:" + std::string(m_lightObject.objName) + " Hash:" + std::to_string(m_lightObject.objHash));
				set_status_text("Failed to load objects");
				return;
			}
		}

		int newObjectRef = OBJECT::CREATE_OBJECT(m_lightObject.objHash, m_lightPosition.x, m_lightPosition.y, m_lightPosition.z, true, true, false);
		m_lightObject.objReference = newObjectRef;
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(newObjectRef, true, true);

		ENTITY::SET_ENTITY_ROTATION(newObjectRef, m_lightRotation.x+180, 0, m_lightRotation.z, 2, true);
	}
}

void StageLight::startTrackActor(Actor actor, int actorIndex)
{
	m_doTrackPed = true;
	m_trackPedId = actor.getActorPed();
	m_trackActorIndex = actorIndex;

	Vector3 currentActorPosition = ENTITY::GET_ENTITY_COORDS(m_trackPedId, true);
	m_trackOffset.x = m_lightPosition.x - currentActorPosition.x;
	m_trackOffset.y = m_lightPosition.y - currentActorPosition.y;
	m_trackOffset.z = m_lightPosition.z - currentActorPosition.z;

}

void StageLight::startTrackActor(Actor actor, int actorIndex, Vector3 trackOffset)
{
	m_doTrackPed = true;
	m_trackPedId = actor.getActorPed();
	m_trackActorIndex = actorIndex;


	m_trackOffset = trackOffset;
}

void StageLight::stopTrackActor()
{
	m_doTrackPed = false;
	m_trackPedId = 0;
	m_trackActorIndex = -1;
	m_trackOffset = Vector3();
}

int StageLight::getTrackedActorIndex()
{
	return m_trackActorIndex;
}

bool StageLight::isTrackingActor()
{
	return m_doTrackPed;
}

bool StageLight::hasFlicker()
{
	return m_hasFlicker;
}

void StageLight::removeLightObject()
{	//delete old object
	if (m_lightObject.objReference != 0) {
		OBJECT::DELETE_OBJECT(&m_lightObject.objReference);
	}
}

void StageLight::turnOff()
{
	if (m_lightObject.objReference != 0) {
		//ENTITY::SET_ENTITY_ALPHA(m_lightObject.objReference, 0, false);
		ENTITY::SET_ENTITY_VISIBLE(m_lightObject.objReference, false, false);
		//log_to_file("Light off");
	}
}

void StageLight::turnOn()
{
	if (m_lightObject.objReference != 0) {
		//ENTITY::SET_ENTITY_ALPHA(m_lightObject.objReference, 255, false);
		ENTITY::SET_ENTITY_VISIBLE(m_lightObject.objReference, true, false);
		//log_to_file("Light on");
	}
}

void StageLight::actionOnTick(DWORD tick, std::vector<Actor>& actors)
{
	if (m_doTrackPed) {
		Vector3 currentActorPosition = ENTITY::GET_ENTITY_COORDS(m_trackPedId, true);
		Vector3 newLightPosition;

		newLightPosition.x = currentActorPosition.x + m_trackOffset.x;
		newLightPosition.y = currentActorPosition.y + m_trackOffset.y;
		newLightPosition.z = currentActorPosition.z + m_trackOffset.z;

		if (newLightPosition.x != m_trackActorLastPos.x || newLightPosition.y != m_trackActorLastPos.y || newLightPosition.z != m_trackActorLastPos.z) {
			moveLight(newLightPosition, m_lightRotation);

			m_trackActorLastPos.x = newLightPosition.x;
			m_trackActorLastPos.y = newLightPosition.y;
			m_trackActorLastPos.z = newLightPosition.z;
		}


	}

	if (m_hasFlicker) {
		if (m_flickerStart == 0) {
			m_flickerStart = tick;
			m_flickerIndex = 0;
		}

		if (m_flickerIndex < m_flickerEvents.size()) {
			StageLightFlicker flickerEvent = m_flickerEvents[m_flickerIndex];
			
			if (tick - flickerEvent.length > m_flickerStart) {
				m_flickerIndex++;
				if (m_flickerIndex >= m_flickerEvents.size()) {
					m_flickerIndex = 0;
				}
				m_flickerStart = tick;
				flickerEvent = m_flickerEvents[m_flickerIndex];
				if (flickerEvent.isOn) {
					
					turnOn();
				}
				else {
					turnOff();
				}
			}
			else {
				//log_to_file("Light not changed " + std::to_string(tick) + " vs " + std::to_string(m_flickerStart + flickerEvent.length));
			}
		}
	}
}

Vector3 StageLight::getLightPosition()
{
	return m_lightPosition;
}

Vector3 StageLight::getLightRotation()
{
	return  m_lightRotation;
}

GTAObject StageLight::getLightObject()
{
	return m_lightObject;
}

Vector3 StageLight::getTrackedActorOffset()
{
	return m_trackOffset;
}
