// Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration
#ifndef MUONANALYSISTOOLS_MUONCALIBRATOR_H
#define MUONANALYSISTOOLS_MUONCALIBRATOR_H

// Framework include(s).
#include <AsgMessaging/AsgMessaging.h>
#include <AsgMessaging/StatusCode.h>
#include <PATInterfaces/SystematicSet.h>

// EDM include(s).
#include <xAODMuon/MuonContainer.h>

// ROOT include(s).
#include <ROOT/RVec.hxx>

// System include(s).
#include <string>
#include <vector>

namespace ATE {

/// EDM-less dummy tool for muon momentum calibration
///
/// It is not meant to be taken seriously. It only tries to demonstrate how
/// a class could be designed so that it could be made use of outside of any
/// framework, and would also provide enough information to be able to
/// conveniently wrap it into an "ATLAS tool".
///
class MuonCalibrator : public asg::AsgMessaging {

public:
    /// Constructor
    MuonCalibrator(const std::string& name = "ATE::MuonCalibrator");
    /// Copy constructor
    MuonCalibrator(const MuonCalibrator& parent);
    /// Move constructor
    MuonCalibrator(MuonCalibrator&& parent);

    /// Initialize the tool
    StatusCode initialize();

    /// @name Systematics related function(s)
    /// @{

    /// Get the list of systematics that affect the tool
    ///
    /// @return The list of systematics that affect the tool
    ///
    CP::SystematicSet affectingSystematics() const;

    /// Get the list of recommended systematics for the tool
    ///
    /// @return The list of recommended systematics for the tool
    ///
    CP::SystematicSet recommendedSystematics() const;

    /// @}

    /// Get the calibrated transverse momentum of a muon
    ///
    /// @param pt The uncalibrated transverse momentum of the muon
    /// @param eta The pseudorapidity of the muon
    /// @param phi The azimuthal angle of the muon
    /// @param syst The systematic variation(s) to apply
    /// @return The calibrated transverse momentum of the muon
    ///
    float getCalibratedPt(float pt, float eta, float phi,
                          const CP::SystematicSet& syst = {}) const;

private:
    /// Calibration data type
    struct CalibData {
        float min_eta = 0.f;
        float max_eta = 0.f;
        float min_phi = 0.f;
        float max_phi = 0.f;
        float min_pt = 0.f;
        float max_pt = 0.f;
        float variation = 0.f;
    };  // struct CalibData

    /// Nominal calibration data
    std::vector<CalibData> m_nominal;
    /// Calibration data for the "MUON_FOO" systematic variation
    std::vector<CalibData> m_foo;
    /// Calibration data for the "MUON_BAR" systematic variation
    std::vector<CalibData> m_bar;

};  // class MuonCalibrator

namespace RDF {

/// Functor that could be used directly with @c ROOT::RDataFrame::Define
class MuonCalibrator : public ATE::MuonCalibrator {

public:
    // Inherit the base class's constructor(s).
    using ATE::MuonCalibrator::MuonCalibrator;

    /// Operator applying the calibration to a single muon
    std::vector<float> operator()(const std::vector<float>& pt,
                                  const std::vector<float>& eta,
                                  const std::vector<float>& phi) const;

};  // class MuonCalibrator

/// Functor that could be used with @c ROOT::RDataFrame::Define, on an xAOD
class MuonCalibratorxAOD : public ATE::MuonCalibrator {

public:
    // Inherit the base class's constructor(s).
    using ATE::MuonCalibrator::MuonCalibrator;

    /// Operator applying the calibration to a single muon
    std::vector<float> operator()(const xAOD::MuonContainer& muon) const;

};  // class MuonCalibratorxAOD

/// Functor that could be used directly with @c ROOT::RDataFrame::Vary
class MuonVariator : public ATE::MuonCalibrator {

public:
    // Inherit the base class's constructor(s).
    using ATE::MuonCalibrator::MuonCalibrator;

    /// Operator applying the calibration to a single muon
    std::vector<ROOT::RVecF> operator()(const std::vector<float>& pt,
                                        const std::vector<float>& eta,
                                        const std::vector<float>& phi) const;

};  // class MuonVariator

/// Functor that could be used with @c ROOT::RDataFrame::Vary, on an xAOD
class MuonVariatorxAOD : public ATE::MuonCalibrator {

public:
    // Inherit the base class's constructor(s).
    using ATE::MuonCalibrator::MuonCalibrator;

    /// Operator applying the calibration to a single muon
    std::vector<ROOT::RVecF> operator()(const xAOD::MuonContainer& muon) const;

};  // class MuonVariatorxAOD

}  // namespace RDF
}  // namespace ATE

#endif  // MUONANALYSISTOOLS_MUONCALIBRATOR_H
