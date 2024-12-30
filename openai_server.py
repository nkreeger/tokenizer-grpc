from fastapi import FastAPI, Request

app = FastAPI()


@app.post("/chat/completions")
async def post_chat_completions(request: Request):

    try:
        request_json = await request.json()
        print(request_json)

        #
        #
        # TODO(kreeger): LEFT OFF RIGHT HERE.
        # -- Need to build a context from this OpenAI client request.
        # -- That context can then be fed to the RPC server with tokens
        #    and maybe some batching stuff.
        #
        #

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
