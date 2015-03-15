#!/bin/bash
grep -Rl "Eclipse\ Public\ License" * | xargs sed -i "s/Eclipse\ Public\ License\ Version\ 1.0/GNU\ General\ Public\ License\ Version\ 3/g"
