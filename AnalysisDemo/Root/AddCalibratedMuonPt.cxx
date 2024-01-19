// Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration

// Local include(s).
#include "AnalysisDemo/AddCalibratedMuonPt.h"

namespace ATE {

AddCalibratedMuonPt::AddCalibratedMuonPt() {
    m_calibrator.initialize().ignore();
}

AddCalibratedMuonPt::AddCalibratedMuonPt(const AddCalibratedMuonPt&) {
    m_calibrator.initialize().ignore();
}

AddCalibratedMuonPt::AddCalibratedMuonPt(AddCalibratedMuonPt&&) {
    m_calibrator.initialize().ignore();
}

std::vector<float> AddCalibratedMuonPt::operator()(
    const xAOD::MuonContainer& muons) const {

    std::vector<float> result;
    result.reserve(muons.size());
    for (const xAOD::Muon* mu : muons) {
        result.push_back(
            m_calibrator.getCalibratedPt(mu->pt(), mu->eta(), mu->phi()));
    }
    return result;
}

}  // namespace ATE
