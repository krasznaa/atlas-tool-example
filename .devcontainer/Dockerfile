# Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration

# Use a specific version of the analysisbase image for development.
FROM gitlab-registry.cern.ch/atlas/athena/analysisbase:24.2.36

# Set up the appropriate environment for VSCode.
COPY vscode_environment.sh /etc/profile.d/

# Start the image simply with bash.
CMD /bin/bash
