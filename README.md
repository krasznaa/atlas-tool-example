# ATLAS Analysis Tool Example

This is a simple demonstrator that showcases how I believe dual/triple-use
tools should be designed for ATLAS. Such that they could be used conveniently
in Athena, EventLoop and "any kind of" columnar analysis as well.

## Building the Project

To build the project on top of AnalysisBase-24.2, you can do something as simple
as:

```
setupATLAS
asetup AnalysisBase,24.2.36
cmake -S atlas-tool-example -B build
cmake --build build
```

To build it on top of AthAnalysis-24.2, you need to tell CMake that it should
use that base project instead. With:

```
setupATLAS
asetup AthAnalysis,24.2.36
cmake -DATE_BASE_PROJECT=AthAnalysis -S atlas-tool-example -B build
cmake --build build
```

## Running the Test Jobs

Once the project is built, and the runtime environment was set up to see the
build results, the following example jobs can be run.
  - When building the project on top of AnalysisBase:
    * `AnalysisDemo_eljob.py`: Runs an EventLoop based job that would use the
      dual-use `ATE::MuonCalibratorTool` for creating a shallow-copied,
      calibrated `xAOD::MuonContainer`;
    * `AnalysisDemo_rdf.py`: Runs a [ROOT::RDataFrame](https://root.cern/doc/v630/classROOT_1_1RDataFrame.html)
      based job that would use the "EDM-less" `ATE::MuonCalibrator` type for
      creating columns with the calibrated muon momenta;
  - When building the project on top of AthAnalysis:
    * `athena.py AnalysisDemo/AnalysisDemo_jobOptions.py`: Run an Athena based
      job that would use the dual-use `ATE::MuonCalibratorTool` for creating a
      shallow-copies, calibrated `xAOD::MuonContainer`;

## Structure of the Project

The project holds just 2 packages, with distinct purposes.
  - [MuonAnalysisTools](MuonAnalysisTools/) is a toy example of what a
    "triple use" muon momentum calibration tool could look like. With some
    very little bells and whistles.
  - [AnalysisDemo](AnalysisDemo/) is a set of "high level" analysis code, which
    would make use of [MuonAnalysisTools](MuonAnalysisTools/) from various
    analysis environments.
