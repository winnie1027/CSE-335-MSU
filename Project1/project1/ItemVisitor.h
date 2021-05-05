/**
 * \file ItemVisitor.h
 *
 * \author Sirena Ly
 *
 * Visitor base class.
 */

#pragma once

class CCargo;
class CBoat;
class CCar;
class CRectangle;
class CHero;
class CDecorItem;
class CVehicle;


/**
 * Defines the base visitor class for CItems.
 */
class CItemVisitor 
{
 public:
  virtual ~CItemVisitor() {}


  /** Visit a CCargo object
   * \param cargo Cargo we are visiting */
  virtual void VisitCargo(CCargo* cargo) {}

  /** Visit a CCargo object
   * \param vehicle Vehicle we are visiting */
  virtual void VisitVehicle(CVehicle *vehicle) {}

  /** Visit a CBoat object
   * \param boat Boat we are visiting */
  virtual void VisitBoat(CBoat *boat) {}

  /** Visit a CCar object
   * \param car Car we are visiting */
  virtual void VisitCar(CCar *car) {}

  /** Visit a CHero object
   * \param hero Hero we are visiting */
  virtual void VisitHero(CHero *hero) {}
  
  /** Visit a CRectangle object
   * \param rectangle Rectangle we are visiting */
  virtual void VisitRectangle(CRectangle *rectangle) {}

  /** Visit a CRectangle object
   * \param decorItem Rectangle we are visiting */
  virtual void VisitDecorItem(CDecorItem *decorItem) {}
};
