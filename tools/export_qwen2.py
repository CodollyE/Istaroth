#!/usr/bin/env python3
"""Placeholder exporter for Qwen2 weights in llama2.c-style workflow."""

from __future__ import annotations

import argparse
from pathlib import Path


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Export Qwen2 HuggingFace checkpoints to Istaroth binary format (placeholder)."
    )
    parser.add_argument("output", type=Path, help="Output .bin path")
    parser.add_argument(
        "--hf",
        required=True,
        help="HuggingFace model name or local path (for example Qwen/Qwen2-0.5B-Instruct)",
    )
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    print("[placeholder] Starting llama2.c-style export pipeline")
    print(f"[placeholder] Source HuggingFace model: {args.hf}")
    print(f"[placeholder] Target binary path: {args.output}")
    print("[placeholder] TODO: load HF weights/tokenizer/config and write fused binary layout.")


if __name__ == "__main__":
    main()
