from fastapi import FastAPI, Request
from transformers import AutoTokenizer

import grpc
import tokenizer_pb2
import tokenizer_pb2_grpc

app = FastAPI()
tokenizer = AutoTokenizer.from_pretrained("meta-llama/Meta-Llama-3-8B")


@app.post("/chat/completions")
async def post_chat_completions(request: Request):

    try:
        request_json = await request.json()

        # Testing only, just one item
        message = request_json['messages'][0]

        # TODO(kreeger): I don't think this is the proper way to format a prompt, but
        # it will work for this demo.
        prompt = "ROLE: {}\nMESSAGE: {}".format(message['role'], message['content'])
        tokens = tokenizer.tokenize(prompt)

        with grpc.insecure_channel("localhost:50051") as channel:
            stub = tokenizer_pb2_grpc.TokenizerStub(channel)

            request = tokenizer_pb2.TokenRequest()
            for token in tokens: 
                request.tokens.append(token)

            response = stub.SendTokens(request)
            print("Tokenizer client received: " + response.message)

    except Exception as e:
        print(e)


    # Mock OpenAI client response - work around actually calling the GPU at all.
    return {
        "id": "chatcmpl-123",
        "object": "chat.completion",
        "created": 1677652288,
        "model": "llama3",
        "system_fingerprint": "fp_44709d6fcb",
        "choices": [
            {
                "index": 0,
                "message": {
                    "role": "assistant",
                    "content": "\n\nHello there, how may I assist you today?",
                },
                "logprobs": None,
                "finish_reason": "stop",
            }
        ],
        "usage": {
            "prompt_tokens": 9,
            "completion_tokens": 12,
            "total_tokens": 21,
            "completion_tokens_details": {
                "reasoning_tokens": 0,
                "accepted_prediction_tokens": 0,
                "rejected_prediction_tokens": 0,
            },
        },
    }


@app.get("/")
def read_root():
    return {"Hello": "World"}
