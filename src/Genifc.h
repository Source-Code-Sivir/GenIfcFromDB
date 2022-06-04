#pragma once
#ifndef GENIFC_H
#define GENIFC_H
#include<memory>
#include<vector>
#include"ifcpp\IFC4\include\IfcReinforcingBar.h"
#include"ifcpp\IFC4\include\IfcCompositeCurve.h"
#include "ifcpp\IFC4\include\IfcReinforcingBarType.h"
#include "ifcpp\IFC4\include\IfcReinforcingBarTypeEnum.h"
#include "ifcpp\IFC4\include\IfcTransitionCode.h"
#include "ifcpp\IFC4\include\IfcTrimmingSelect.h"
#include "ifcpp\IFC4\include\IfcTrimmingPreference.h"
#include "ifcpp\IFC4\include\IfcLine.h"
#include "ifcpp\IFC4\include\IfcVector.h"
#include "ifcpp/IFC4/include/IfcGloballyUniqueId.h"
#include "ifcpp/IFC4/include/IfcOwnerHistory.h"
#include "ifcpp/IFC4/include/IfcText.h"
#include "ifcpp/IFC4/include/IfcAreaMeasure.h"
#include "ifcpp/IFC4/include/IfcVolumeMeasure.h"
#include "ifcpp/IFC4/include/IfcPlaneAngleMeasure.h"
#include "ifcpp/IFC4/include/IfcSolidAngleMeasure.h"
#include "ifcpp/IFC4/include/IfcTimeMeasure.h"
#include "ifcpp/IFC4/include/IfcMassMeasure.h"
#include "ifcpp/IFC4/include/IfcThermodynamicTemperatureMeasure.h"
#include "ifcpp/IFC4/include/IfcLuminousIntensityMeasure.h"
#include "ifcpp\IFC4\include\IfcDerivedUnitEnum.h"
#include "ifcpp\IFC4\include\IfcVolumetricFlowRateMeasure.h"
#include "ifcpp\IFC4\include\IfcGeometricProjectionEnum.h"
#include "ifcpp\IFC4\include\IfcProfileTypeEnum.h"
#include "ifcpp\IFC4\include\IfcReflectanceMethodEnum.h"
#include "ifcpp\IFC4\include\IfcSurfaceSide.h"
#include"ifcpp/IFC4\include\IfcCompositeCurveSegment.h"
#include"ifcpp/IFC4\include\IfcBoolean.h"
#include"ifcpp\IFC4\include\IfcTrimmedCurve.h"
#include"ifcpp\IFC4\include\IfcParameterValue.h"
#include"ifcpp\IFC4\include\IfcCartesianPoint.h"
#include"ifcpp\IFC4\include\IfcLengthMeasure.h"
#include"ifcpp\IFC4\include\IfcVector.h"
#include"ifcpp\IFC4\include\IfcDirection.h"
#include"ifcpp\IFC4\include\IfcReal.h"
#include"ifcpp\IFC4\include\IfcCircle.h"
#include"ifcpp\IFC4\include\IfcPositiveLengthMeasure.h"
#include"ifcpp\IFC4\include\IfcAxis2Placement3D.h"
#include"ifcpp\IFC4\include\IfcAxis2Placement.h"
#include"ifcpp\IFC4\include\IfcDirection.h"
#include"ifcpp\IFC4\include\IfcRepresentationMap.h"
#include"ifcpp\IFC4\include\IfcRepresentation.h"
#include"ifcpp\IFC4\include\IfcSweptDiskSolid.h"
#include"ifcpp\IFC4\include\IfcShapeRepresentation.h"
#include"ifcpp\IFC4\include\IfcTrimmingPreference.h"
#include"ifcpp\IFC4\include\IfcGeometricRepresentationContext.h"
#include"ifcpp\IFC4\include\IfcMappedItem.h"
#include"ifcpp\IFC4\include\IfcCartesianTransformationOperator3D.h"
#include"ifcpp\IFC4\include\IfcProductDefinitionShape.h"
#include"ifcpp\IFC4\include\IfcLocalPlacement.h"
#include"ifcpp\IFC4\include\IfcLogical.h"
#include"ifcpp\IFC4\include\IfcReinforcingBarSurfaceEnum.h"
#include"ifcpp\IFC4\include\IfcLabel.h"
#include"ifcpp\IFC4\include\IfcIdentifier.h"
#include"ifcpp\IFC4\include\IfcVector.h"
namespace GenIfc {
	std::shared_ptr<IfcCartesianPoint> GenIfcCartesianPoint(std::vector<double> &data);

	std::shared_ptr<IfcDirection> GenIfcDirection(std::vector<double> &data);

	std::shared_ptr<IfcAxis2Placement3D> GenIfcAxis2Placement3D(shared_ptr<IfcCartesianPoint> &point,
		shared_ptr<IfcDirection>&dx, shared_ptr<IfcDirection>&dz);

	std::shared_ptr<IfcTrimmedCurve> GenIfcTrimmedCurve(shared_ptr<IfcCurve> &curve, double trim1, double trim2,
		bool direction, IfcTrimmingPreference::IfcTrimmingPreferenceEnum perf);
		//目前只支持用para初始化，如果想用point来初始化请自己写重载函数

	std::shared_ptr<IfcLine> GenIfcLine(shared_ptr<IfcCartesianPoint> &point, shared_ptr<IfcDirection> dir);

	std::shared_ptr<IfcCircle> GenIfcCircle(double radius, shared_ptr<IfcAxis2Placement3D> &placement);

	std::shared_ptr<IfcCompositeCurveSegment> GenIfcCompositeCurveSegment(IfcTransitionCode::IfcTransitionCodeEnum e, bool same, 
		shared_ptr<IfcCurve> &curve);

	std::shared_ptr<IfcCompositeCurve> GenIfcCompositeCurve(std::vector <shared_ptr<IfcCompositeCurveSegment>>& curv, LogicalEnum a);

	std::shared_ptr<IfcSweptDiskSolid> GenIfcSweptDiskSolid(shared_ptr<IfcCurve> curve, double radius,
		double innerradius, double start, double end);

	std::shared_ptr<IfcShapeRepresentation> GenIfcShapeRepresentation(shared_ptr<IfcRepresentationContext> context,
		const char *m_RepresentationIdentifier, const char*m_RepresentationType,
		std::vector<shared_ptr<IfcRepresentationItem>>&m_Items);

	std::shared_ptr<IfcRepresentationContext> GenIfcRepresentationContext();

	std::shared_ptr<IfcGeometricRepresentationContext> GenIfcGeometricRepresentationContext(const char*m_ContextIdentifier,
		const char*m_ContextType, shared_ptr<IfcDimensionCount>m_CoordinateSpaceDimension, double precision,
		shared_ptr<IfcAxis2Placement> place, shared_ptr<IfcDirection> dir);

	std::shared_ptr<IfcRepresentationMap> GenIfcRepresentationMap(shared_ptr<IfcAxis2Placement3D> &origin,
		shared_ptr<IfcRepresentation> pre);

	std::shared_ptr<IfcMappedItem> GenIfcMappedItem(shared_ptr<IfcRepresentationMap> map,
		shared_ptr<IfcCartesianTransformationOperator> pre);

	std::shared_ptr<IfcCartesianTransformationOperator> GenIfcCartesianTransformationOperator3D(shared_ptr<IfcDirection> d1,
		shared_ptr<IfcDirection>d2, shared_ptr<IfcCartesianPoint> point, shared_ptr<IfcReal> r,shared_ptr<IfcDirection>d3);

	std::shared_ptr<IfcProductDefinitionShape> GenIfcProductDefinitionShape(const char *name, const char *desc,
		std::vector<shared_ptr<IfcRepresentation>> repres);

	std::shared_ptr<IfcLocalPlacement> GenIfcLocalPlacement(shared_ptr<IfcObjectPlacement> localplace,
		shared_ptr<IfcAxis2Placement> place);

	std::shared_ptr<IfcReinforcingBar> GenIfcReinforcingBar(const char* id, shared_ptr<IfcOwnerHistory> owner,
		const char* name, const char* desc, const char* objtype, shared_ptr<IfcObjectPlacement> objplace,
		shared_ptr<IfcProductRepresentation> repre, const char* tag, const char* steel,
		double diameter, double area, double len,
		IfcReinforcingBarTypeEnum predefinedtype, IfcReinforcingBarSurfaceEnum surface);
	
	std::shared_ptr< IfcCartesianTransformationOperator> GenIfcCartesianTransformationOperator(shared_ptr<IfcDirection>axis1, shared_ptr<IfcDirection>axis2, shared_ptr<IfcCartesianPoint> point, shared_ptr<IfcReal> real);

	std::shared_ptr<IfcCompositeCurveSegment> GenIfcCompositeCurveSegment(shared_ptr<IfcTransitionCode>m_Transition, bool m_SameSense, shared_ptr<IfcCurve> m_ParentCurve);

}
#endif
