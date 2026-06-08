//
// Created by nuelex on 25/05/25.
//

#include "CameraPTUImpl.hpp"


void CameraPTUImpl::transform(const Rotater& rotater)
{
    auto radRotater = radFromDegree(rotater);
    radRotater.setCenter(this->getPosition());

    const Mover backMover = -radRotater.centerToMover();
    const Mover fwdMover = radRotater.centerToMover();

    _target.move(backMover.getDx(), backMover.getDy(), backMover.getDz());
    _target.rotate(radRotater.getOx(), radRotater.getOy(), radRotater.getOz());
    _target.move(fwdMover.getDx(), fwdMover.getDy(), fwdMover.getDz());
}

void CameraPTUImpl::transform(const Mover& mover)
{
    _position.move(mover.getDx(), mover.getDy(), mover.getDz());
    _target.move(mover.getDx(), mover.getDy(), mover.getDz());
}

Rotater CameraPTUImpl::radFromDegree(const Rotater& rotater)
{
    return {rotater.getOx() * M_PI / 180,
            rotater.getOy() * M_PI / 180,
            rotater.getOz() * M_PI / 180,
            rotater.getCenter()};
}
