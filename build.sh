#!/usr/bin/env sh

cd DynamoEngine && make -Bj && cd ..
cd Ballista && make -Bj && cd .. && echo "Build complete!"