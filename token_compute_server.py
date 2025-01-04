#
# TokenRequest RPC handler.
# Start this work in Python - determine what makes sense in c++ (e.g. queuing, etc)
#

from concurrent import futures
import logging

import grpc
import tokenizer_pb2
import tokenizer_pb2_grpc


class TokenComputeServer(tokenizer_pb2_grpc.TokenizerServicer):
    def __init__(self):
        pass

    def SendTokens(self, request: tokenizer_pb2.TokenRequest, context):
        """Sends a greeting
        """
        print("Hi from TokenComputeServer.SendTokens()")
        print("uuid: {}".format(request.uuid))
        print("model: {}".format(request.model_name))

        for token in request.prompt_tokens:
            print(token)
        print("-----------------------------")

        return tokenizer_pb2.TokenRequestReply(message="A response...")


def serve():
    port = "50051"
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    tokenizer_pb2_grpc.add_TokenizerServicer_to_server(TokenComputeServer(), server)
    server.add_insecure_port("[::]:" + port)
    server.start()
    print("Server started, listening on " + port)
    server.wait_for_termination()


if __name__ == "__main__":
    logging.basicConfig()
    serve()
