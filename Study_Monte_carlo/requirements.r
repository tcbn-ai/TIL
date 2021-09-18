# install some packages
install.packages(c("latex2exp",
    "MASS",
    "ggplot2",
    "plotly",
    "xaringan"))

# install dependencies of yuima
install.packages(c("cubature",
    "glassoFast",
    "wavethresh", 
    "coda", 
    "RcppArmadillo"))

# install yuima
# Reference: https://rdrr.io/rforge/yuima/
install.packages("yuima", repos=c("http://R-Forge.R-project.org"), dependencies =TRUE)
