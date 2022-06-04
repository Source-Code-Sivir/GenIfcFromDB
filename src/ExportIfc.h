#pragma once
#ifndef EXPORTIFC_H
#define EXPORTIFC_H
#include<iostream>
#include<fstream>

#include "ifcpp/model/BuildingModel.h"
#include "ifcpp/reader/ReaderUtil.h"
#include "ifcpp/writer/WriterSTEP.h"
#include "ifcpp/writer/WriterUtil.h"

#include "ifcpp/model/BuildingModel.h"
#include "ifcpp/model/UnitConverter.h"
#include "ifcpp/model/BuildingGuid.h"

#include "ifcpp/IFC4/include/IfcArbitraryClosedProfileDef.h"
#include "ifcpp/IFC4/include/IfcAxis2Placement3D.h"
#include "ifcpp/IFC4/include/IfcBoolean.h"
#include "ifcpp/IFC4/include/IfcBoundingBox.h"
#include "ifcpp/IFC4/include/IfcBuilding.h"
#include "ifcpp/IFC4/include/IfcBuildingStorey.h"
#include "ifcpp/IFC4/include/IfcCartesianPoint.h"
#include "ifcpp/IFC4/include/IfcClosedShell.h"
#include "ifcpp/IFC4/include/IfcDimensionCount.h"
#include "ifcpp/IFC4/include/IfcDimensionalExponents.h"
#include "ifcpp/IFC4/include/IfcDirection.h"
#include "ifcpp/IFC4/include/IfcExtrudedAreaSolid.h"
#include "ifcpp/IFC4/include/IfcFace.h"
#include "ifcpp/IFC4/include/IfcFacetedBrep.h"
#include "ifcpp/IFC4/include/IfcFaceOuterBound.h"
#include "ifcpp/IFC4/include/IfcGeometricRepresentationContext.h"
#include "ifcpp/IFC4/include/IfcGloballyUniqueId.h"
#include "ifcpp/IFC4/include/IfcIdentifier.h"
#include "ifcpp/IFC4/include/IfcLabel.h"
#include "ifcpp/IFC4/include/IfcLengthMeasure.h"
#include "ifcpp/IFC4/include/IfcLocalPlacement.h"
#include "ifcpp/IFC4/include/IfcOpeningElement.h"
#include "ifcpp/IFC4/include/IfcOrganization.h"
#include "ifcpp/IFC4/include/IfcOwnerHistory.h"
#include "ifcpp/IFC4/include/IfcPerson.h"
#include "ifcpp/IFC4/include/IfcPersonAndOrganization.h"
#include "ifcpp/IFC4/include/IfcPolyline.h"
#include "ifcpp/IFC4/include/IfcPolyLoop.h"
#include "ifcpp/IFC4/include/IfcPositiveLengthMeasure.h"
#include "ifcpp/IFC4/include/IfcProductDefinitionShape.h"
#include "ifcpp/IFC4/include/IfcPropertySet.h"
#include "ifcpp/IFC4/include/IfcPropertySingleValue.h"
#include "ifcpp/IFC4/include/IfcReal.h"
#include "ifcpp/IFC4/include/IfcRelAggregates.h"
#include "ifcpp/IFC4/include/IfcRelContainedInSpatialStructure.h"
#include "ifcpp/IFC4/include/IfcRelDefinesByProperties.h"
#include "ifcpp/IFC4/include/IfcRelVoidsElement.h"
#include "ifcpp/IFC4/include/IfcShapeRepresentation.h"
#include "ifcpp/IFC4/include/IfcSite.h"
#include "ifcpp/IFC4/include/IfcSIUnit.h"
#include "ifcpp/IFC4/include/IfcText.h"
#include "ifcpp/IFC4/include/IfcUnitAssignment.h"
#include "ifcpp/IFC4/include/IfcUnitEnum.h"
#include "ifcpp/IFC4/include/IfcWall.h"
#include "ifcpp/IFC4/include/IfcReinforcingBar.h"
//#include"ifcpp/model\BuildGuid.h"


//void convertPlacement(double local_x[3], double local_z[3], double location[3], shared_ptr<IfcAxis2Placement3D>& axis2placement3d, std::vector<shared_ptr<BuildingEntity> >& vec_new_entities);
class ExportIfc {
public:
	shared_ptr<BuildingModel> ifc_model;
	ExportIfc() {
		ifc_model = make_shared<BuildingModel>();
	}
	void initIfcModel(shared_ptr<IfcReinforcingBar> bar, std::vector<shared_ptr<BuildingEntity>>& vec_new_entities);
	
	void exportifc();
	/*void handle(std::vector<shared_ptr<BuildingEntity>>& vec_new_entities) {
		
		
	}*/
};


#endif // !EXPORTIFC_H
