This is a forked maintenance repo of [OnTAD](https://github.com/anlin00007/OnTAD/) (forked at v1.4).

## Changes

- Container image is now smaller with debian:bookworm-slim

## Docker

Container images are published to GHCR. Workdir is /data and entrypoint is not set in this fork. Specify OnTAD explicitly in the command line to run.

```
docker run --rm -v "$PWD:/data" ghcr.io/snsinfu/anlin00007-ontad:v1.4 OnTAD input.mat -o out ...
```

## Reference

Lin An, Tao Yang, Jiahao Yang, Johannes Nuebler, Guanjue Xiang, Ross C. Hardison, Qunhua Li*, Yu Zhang*. OnTAD: Hierarchical Domain Structure Reveals the Divergence of Activity among TADs and Boundaries, Genome Biology 2019 (https://doi.org/10.1186/s13059-019-1893-y)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
