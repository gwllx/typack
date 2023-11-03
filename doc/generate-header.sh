#!/bin/bash

# Generate Doxygen templates.
doxygen -w html header.html footer.html style.css

# Remove unnecessary templates.
rm footer.html
rm style.css

# Insert doxygen-awesome-css extensions before '$treeview'.
sed -i '' -e '/^\$treeview$/{r header.html.in' -e 'N' -e '}' header.html
