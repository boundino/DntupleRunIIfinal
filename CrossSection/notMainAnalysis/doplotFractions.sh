#!/bin/bash

root -b -q "plotFractions.C+(\"PbPb\",100)"
root -b -q "plotFractions.C+(\"PbPb\",10)"
root -b -q "plotFractions.C+(\"PP\")"

