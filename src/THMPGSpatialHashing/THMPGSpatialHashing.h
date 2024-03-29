/******************************************************************************
*                 SOFA, Simulation Open-Framework Architecture                *
*                    (c) 2006 INRIA, USTL, UJF, CNRS, MGH                     *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#pragma once

#include <THMPGSpatialHashing/config.h>

#include <sofa/core/collision/BroadPhaseDetection.h>
#include <sofa/core/collision/NarrowPhaseDetection.h>
#include <sofa/core/CollisionElement.h>
#include <sofa/core/collision/NarrowPhaseDetection.h>

#include <sofa/type/Vec.h>
#include <set>
#include <boost/unordered_map.hpp>
#include <sofa/core/CollisionModel.h>
#include <THMPGSpatialHashing/THMPGHashTable.h>
#include <sofa/core/topology/BaseMeshTopology.h>
#include <sofa/core/behavior/BaseMechanicalState.h>
#include <sofa/core/behavior/MechanicalState.h>
#include <sofa/simulation/ResetVisitor.h>
#include <boost/unordered_map.hpp>

namespace sofa::component::collision
{

using namespace sofa::defaulttype;

class SOFA_THMPGSPATIALHASHING_API THMPGSpatialHashing:
    public core::collision::BroadPhaseDetection,
    public core::collision::NarrowPhaseDetection
{
public:
    SOFA_CLASS2(THMPGSpatialHashing, core::collision::BroadPhaseDetection, core::collision::NarrowPhaseDetection);

private:
    template <class DataTypes>
    void sumEdgeLength_template(core::CollisionModel *cm);
protected:
    THMPGSpatialHashing();

    ~THMPGSpatialHashing() override{}

    virtual bool keepCollisionBetween(core::CollisionModel *cm1, core::CollisionModel *cm2);

    void sumEdgeLength(core::CollisionModel *cm);

    //boost::unordered_map<std::pair<core::CollisionModel*,core::CollisionModel*>,CollidingPair> _qsdf;

    sofa::type::vector<sofa::component::collision::geometry::CubeCollisionModel*> cubeModels;//AABBs containing the final collision model
    THMPGHashTable _grid;
    SReal _timeStamp;
    SReal _cell_size;
    bool _params_initialized;
    SReal _nb_edges;
    SReal _nb_elems;
    SReal _total_edges_length;
    int _max_cm_size;
    std::vector<core::CollisionModel*> _collisionModels;
    boost::unordered::unordered_map<sofa::core::CollisionModel*,THMPGHashTable> _hash_tables;
public:
    inline void beginBroadPhase() override
    {
        core::collision::BroadPhaseDetection::beginBroadPhase();
        _timeStamp += this->getContext()->getDt();
        _collisionModels.clear();
    }


    void init() override;
    void reinit() override;

    void addCollisionModel (core::CollisionModel *cm) override;

    void endBroadPhase() override;

    /**
      *Unuseful methods because all is done in addCollisionModel
      */
    void addCollisionPair (const std::pair<core::CollisionModel*, core::CollisionModel*>& ) override;

    void beginNarrowPhase() override;


    /* for debugging */
    inline void draw(const core::visual::VisualParams*) override{}

    inline bool needsDeepBoundingTree()const override{return false;}
};

} // namespace sofa::component::collision
