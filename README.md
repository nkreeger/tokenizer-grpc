# Stub project for OpenAI client -> Python OpenAI Server FE -> C++ gRPC CUDA Backend

Ensure this is set
```sh
export CUDACXX=/usr/local/cuda-12/bin/nvcc
```

1. Ensure venv - use `requirements.txt`
2. Cmake build `mkdir build && cd build && make -G Ninja .. && ninja`
3. Build and install gRPC
4. Start gRPC server
5. Run python FE `fastapi dev openai_server.py`
6. Send mock OpenAI request `python send_openqi_request.py`