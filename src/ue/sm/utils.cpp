//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#include "sm.hpp"
#include <nas/utils.hpp>
#include <ue/app/task.hpp>
#include <ue/mm/mm.hpp>

namespace nr::ue
{

bool NasSm::checkPtiAndPsi(const nas::SmMessage &msg)
{
    if (msg.pti < ProcedureTransaction::MIN_ID || msg.pti > ProcedureTransaction::MAX_ID)
    {
        m_logger->err("Received PTI [%d] value is invalid", msg.pti);
        sendSmCause(nas::ESmCause::INVALID_PTI_VALUE, msg.pti, msg.pduSessionId);
        return false;
    }

    if (m_procedureTransactions[msg.pti].psi != msg.pduSessionId)
    {
        m_logger->err("Received PSI value [%d] is invalid, expected was [%d]", msg.pduSessionId,
                      m_procedureTransactions[msg.pti].psi);
        sendSmCause(nas::ESmCause::INVALID_PTI_VALUE, msg.pti, msg.pduSessionId);
        return false;
    }

    return true;
}

} // namespace nr::ue